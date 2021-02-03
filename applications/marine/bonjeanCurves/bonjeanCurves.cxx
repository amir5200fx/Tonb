#include <Pnt2d.hxx>
#include <TecPlot.hxx>
#include <Entity3d_Box.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <HydStatic_Bonjean.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <Geom2d_Curve.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <vector>

namespace tnbLib
{

	static const std::shared_ptr<HydStatic_Bonjean> bonjeanMaker = std::make_shared<HydStatic_Bonjean>();

	static int nbPoints = 100;

	typedef std::shared_ptr<Marine_Body> body_t;
	typedef std::shared_ptr<marineLib::Body_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Body_Displacer> displacer_t;
	typedef std::shared_ptr<HydStatic_Spacing> spacing_t;
	typedef std::shared_ptr<Marine_MultLevWaterDomain> domains_t;

	static size_t verbose = 0;
	static domains_t myDomains;

	const auto& getBnjMaker()
	{
		return bonjeanMaker;
	}

	/*void loadSpacing(const spacing_t& t)
	{
		getBnjMaker()->LoadWaters(t);
	}*/

	void perform()
	{
		getBnjMaker()->Perform();
	}

	/*auto discretize(const Geom2d_Curve& c)
	{
		auto n = std::max(nbPoints, 10);
		const auto du = (c.LastParameter() - c.FirstParameter()) / (double)(n - 1);
		auto u0 = c.FirstParameter();
		std::vector<Pnt2d> pnts;
		pnts.reserve(n);
		for (size_t i = 0; i <= n; i++)
		{
			auto u = u0 + i * du;
			auto gPnt = c.Value(u);
			auto pt = Pnt2d(std::move(gPnt));
			pnts.push_back(std::move(pt));
		}
		return std::move(pnts);
	}*/

	//- io functions

	void loadWaters(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myDomains;
		const auto& body = myDomains->Body();

		if (body->IsHull())
		{
			if (NOT std::dynamic_pointer_cast<marineLib::Body_Displacer>(body))
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body type!" << endl
					<< abort(FatalError);
			}
		}
		else if (body->IsSail())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid body type!" << endl
				<< abort(FatalError);
		}

		if (body->NbSections() < 3)
		{
			FatalErrorIn(FunctionSIG)
				<< "the body must have 3 sections at least" << endl
				<< abort(FatalError);
		}

		getBnjMaker()->LoadWaters(myDomains);

		if (verbose)
		{
			Info << endl;
			Info << " the body is loaded, successfully!" << endl;
			Info << endl;
		}
	}

	/*void exportToPlt(const std::shared_ptr<Marine_Graph>& g, const std::string& name)
	{
		if (g)
		{
			fileName fn(name);
			OFstream f(fn);

			const auto& curves = g->Curves();
			for (const auto& x : curves)
			{
				auto pnts = discretize(*x->Curve());
				Io::ExportCurve(pnts, f);
			}
		}
	}*/

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive ar(f);

		ar << bonjeanMaker;

		if (verbose)
		{
			Info << endl;
			Info << " the Bonjean-curves is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {perform(); }), "execute");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadWaters(name); }), "loadWaters");
		mod->add(chaiscript::fun([](unsigned short c)-> void {HydStatic_Bonjean::verbose = c; verbose = c; }), "setVerbose");

	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char *argv[])
{

	FatalError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("bonjeanCurves");

			try
			{
				chai.eval_file(myFileName);
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}
#include <Pnt2d.hxx>
#include <TecPlot.hxx>
#include <Entity3d_Box.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
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

	const auto& getBnjMaker()
	{
		return bonjeanMaker;
	}

	void loadSpacing(const spacing_t& t)
	{
		getBnjMaker()->LoadWaters(t);
	}

	auto createDomain_tank(const tank_t& b)
	{
		auto domain = Marine_WaterLib::Domain(*b);
		return std::move(domain);
	}

	auto createDomain_displacer(const displacer_t& b)
	{
		auto domain = Marine_WaterLib::Domain(*b);
		return std::move(domain);
	}

	std::shared_ptr<Marine_Domain> createDomain(const body_t& b)
	{
		if (b->IsHull())
		{
			auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(b);
			if (body)
			{
				auto t = createDomain_displacer(body);
				return std::move(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body" << endl
					<< abort(FatalError);
				return nullptr;
			}
		}
		else if (b->IsTank())
		{
			auto body = std::dynamic_pointer_cast<marineLib::Body_Tank>(b);
			if (body)
			{
				auto t = createDomain_tank(body);
				return std::move(t);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid body" << endl
					<< abort(FatalError);
				return nullptr;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid body" << endl
				<< abort(FatalError);
			return nullptr;
		}
	}

	auto calcUniformSpacing(const body_t& b, const Entity3d_Box& box, int n)
	{
		const auto z0 = box.P0().Z();
		const auto z1 = box.P1().Z();

		n = std::max(n, 5);
		const auto dz = (z1 - z0) / (Standard_Real)(n - 1);

		auto spacing = std::make_shared<HydStatic_UniformSpacing>(n);
		spacing->SetLower(z0 + 0.5*dz);
		spacing->SetUpper(z1 + 0.5*dz);
		return std::move(spacing);
	}

	void createUniformSpacing(int n)
	{
		const auto& domain = getBnjMaker()->Domain();
		if (NOT domain)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been loaded!" << endl
				<< abort(FatalError);
		}

		auto spacing = calcUniformSpacing(getBnjMaker()->Body(), *domain->Dim(), n);
		getBnjMaker()->LoadWaters(spacing);
	}

	void perform()
	{
		if (NOT getBnjMaker()->Waters())
		{
			createUniformSpacing(15);
		}
		getBnjMaker()->Perform();
	}

	auto discretize(const Geom2d_Curve& c)
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
	}

	//- io functions

	void loadBody(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		body_t body;
		ar >> body;

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

		auto domain = createDomain(body);

		getBnjMaker()->LoadBody(body);
		getBnjMaker()->LoadDomain(domain);
	}

	void exportToPlt(const std::shared_ptr<Marine_Graph>& g, const std::string& name)
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

		mod->add(chaiscript::fun([](int n)->void {createUniformSpacing(n); }), "createUniformSpacing");
		mod->add(chaiscript::fun([]()->void {perform(); }), "execute");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadBody(name); }), "loadBody");

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

			

			chai.add(mod);

			fileName myFileName("hydStaticModel");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}
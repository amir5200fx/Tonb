#include <Pnt2d.hxx>
#include <TecPlot.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <MarineBase_Tools.hxx>
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

	typedef std::shared_ptr<HydStatic_Bonjean> bonjean_t;

	static bonjean_t myBonjean;
	static size_t verbose = 0;

	static int nbPnts = 25;


	enum class discreteLevel
	{
		low,
		medium,
		high
	};

	discreteLevel myLevel;

	void setLevel(const std::string& l)
	{
		if (l IS_EQUAL "low")
		{
			myLevel = discreteLevel::low;
		}
		else if (l IS_EQUAL "medium")
		{
			myLevel = discreteLevel::medium;
		}
		else if (l IS_EQUAL "high")
		{
			myLevel = discreteLevel::high;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified level of discretization" << endl
				<< abort(FatalError);
		}
	}

	void loadBonjean(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the Bonjean-curves..." << endl;
			Info << endl;
		}

		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myBonjean;

		if (NOT myBonjean)
		{
			FatalErrorIn(FunctionSIG)
				<< " the Bonjean-curves graph is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the Bonjean-curves is loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto discretize(const Geom2d_Curve& c)
	{
		switch (myLevel)
		{
		case tnbLib::discreteLevel::low:
			nbPnts = 25;
			break;
		case tnbLib::discreteLevel::medium:
			nbPnts = 50;
			break;
		case tnbLib::discreteLevel::high:
			nbPnts = 100;
			break;
		default:
			FatalErrorIn(FunctionSIG)
				<< "Unspecified level of discretization" << endl
				<< abort(FatalError);
			break;
		}
		auto n = nbPnts;
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

	void exportToPlt(const std::string& name)
	{
		if (NOT myBonjean)
		{
			FatalErrorIn(FunctionSIG)
				<< "no Bonjean-curves is loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		OFstream f(fn);

		const auto& curves = myBonjean->Graph()->Curves();
		if (curves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the graph has no curve!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " the level of the discretization is set to:" << endl;
			switch (myLevel)
			{
			case tnbLib::discreteLevel::low:
				Info << " low" << endl;
				break;
			case tnbLib::discreteLevel::medium:
				Info << " medium" << endl;
				break;
			case tnbLib::discreteLevel::high:
				Info << " high" << endl;
				break;
			default:
				FatalErrorIn(FunctionSIG)
					<< "Unspecified level of discretization" << endl
					<< abort(FatalError);
				break;
			}
		}

		auto tot = std::make_shared<Entity2d_Chain>();
		for (const auto& x : curves)
		{
			auto pnts = discretize(*x->Curve());
			auto indices = dualConnectivityList_Chain((int)pnts.size() - 1);
			auto chain = std::make_shared<Entity2d_Chain>(std::move(pnts), std::move(indices));

			tot->Add(*chain);
		}
		tot->ExportToPlt(f);

		if (verbose)
		{
			Info << endl;
			Info << " the Bonjean-curves is exported to the Tecplot, successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& l)->void {setLevel(l); }), "setDiscreteLevel");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadBonjean(name); }), "loadBonjean");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(name); }), "exportToPlt");
		mod->add(chaiscript::fun([](unsigned short c)-> void {verbose = c; }), "setVerbose");

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

			fileName myFileName("TnbBonjeanViewer");

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
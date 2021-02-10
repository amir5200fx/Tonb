#include <Geo_Tools.hxx>
//#include <Marine_System.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_CmptLib2.hxx>
#include <Marine_Models.hxx>
#include <HydStatic_HydCurves.hxx>
#include <HydStatic_HydCurvesGraph.hxx>
#include <HydStatic_HydGphCurve.hxx>
#include <StbGMaker_Model.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <algorithm>
#include <vector>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<HydStatic_HydCurvesGraph> curves_t;

	static curves_t myCurves;
	static size_t verbose(0);

	static const unsigned int DEFAULT_NB_DIVISIONS_LOW = 15;
	static const unsigned int DEFAULT_NB_DIVISIONS_MEDIUM = 25;
	static const unsigned int DEFAULT_NB_DIVISIONS_HIGH = 60;

	static auto nPnts = DEFAULT_NB_DIVISIONS_LOW;

	void setTessellation(const word& t)
	{
		if (t IS_EQUAL "low")
		{
			nPnts = DEFAULT_NB_DIVISIONS_LOW;
		}
		else if (t IS_EQUAL "medium")
		{
			nPnts = DEFAULT_NB_DIVISIONS_MEDIUM;
		}
		else if (t IS_EQUAL "high")
		{
			nPnts = DEFAULT_NB_DIVISIONS_HIGH;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined tessellation type" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the tessellation level is set to: " << t << endl;
			Info << endl;
		}
	}

	void loadCurves(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myCurves;

		if (NOT myCurves)
		{
			FatalErrorIn(FunctionSIG)
				<< "the graph is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the curves have been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto getPoints(const Handle(Geom2d_Curve)& theCurve)
	{
		const auto u1 = theCurve->LastParameter();
		const auto u0 = theCurve->FirstParameter();

		const auto du = (u1 - u0) / (Standard_Real)(nPnts - 1);
		std::vector<Pnt2d> pnts;
		pnts.reserve(nPnts);
		for (size_t i = 0; i < nPnts; i++)
		{
			auto pt = theCurve->Value(u0 + i * du);
			pnts.push_back(std::move(pt));
		}
		return std::move(pnts);
	}

	void exportToPlt(const std::string& name)
	{
		const auto& curves = myCurves->Curves();
		size_t i = 0;
		for (const auto& x : curves)
		{

			Debug_Null_Pointer(x);
			const auto& g = x->Geometry();

			/*std::string address = ".\\" + std::string(x->Name()) + "\\" + name;
			std::string dirName = x->Name().c_str();
			boost::filesystem::path dir(dirName);*/
			Info << "name: " << x->Name() << endl;
			std::string address = ".\\" + std::string(x->Name()) + "\\" + name;
			boost::filesystem::path dir(std::string(x->Name()));
			boost::filesystem::create_directory(dir);

			OFstream f(address);

			auto pnts = getPoints(g);
			Io::ExportCurve(pnts, f);

			if (verbose)
			{
				Info << endl;
				Info << " the " << x->Name() << " graph is exported to: " << address << ", successfully!" << endl;
				Info << endl;
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
		mod->add(chaiscript::fun([](const std::string& t)-> void {setTessellation(t); }), "setTessellation");
		mod->add(chaiscript::fun([](unsigned int i)-> void {verbose = i; }), "setVerbose");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCurves(name); }), "loadGraph");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
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
	//sysLib::init_gl_marine_integration_info();
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

			fileName myFileName("hydStaticCurvesViewer");

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
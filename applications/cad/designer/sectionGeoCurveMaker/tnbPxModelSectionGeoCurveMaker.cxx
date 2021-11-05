#include <Pln_Curve.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_CurveQ.hxx>
#include <SectPx_Pole.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <Standard_Failure.hxx>

#include <map>

namespace tnbLib
{
	static const std::string loadExt = SectPx_FrameTuner::extension;
	static const std::string saveExt = Pln_Curve::extension;

	static appl::tuner_t myTuner;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static std::string myFileName;

	static int degree = 3;

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static std::shared_ptr<maker::CurveQ> myCurveMaker;
	static std::map<int, std::shared_ptr<Pln_Curve>> myCurveMap;

	//- globals

	void checkFrame()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	const auto& getFrameRegistry()
	{
		checkFrame();
		return myTuner->FrameRegistry();
	}

	const auto& getScatterReg()
	{
		checkFrame();
		return myTuner->FrameRegistry()->Scatter();
	}

	void loadTuner(const std::string& name)
	{
		file::CheckExtension(name);

		fileName fn(name + loadExt);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive ia(f);

		ia >> myRegistry;
		ia >> myTuner;

		if (verbose)
		{
			Info << endl;
			Info << " the tuner has been loaded successfully!" << endl;
			Info << endl;
		}

		if (NOT myRegistry)
		{
			FatalErrorIn(FunctionSIG)
				<< " the registry is null" << endl
				<< abort(FatalError);
		}

		if (NOT myTuner)
		{
			FatalErrorIn(FunctionSIG)
				<< "no tuner has been detected" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->FrameRegistry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no registry has been detected for the frame" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->IsFrameLoaded())
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded into the tuner!" << endl
				<< abort(FatalError);
		}

		myCurveMaker = std::make_shared<maker::CurveQ>(myTuner->FrameRegistry());
		loadTag = true;
	}

	void loadTuner()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadTuner(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " nb. of curves are going to be saved: " << myCurveMap.size() << endl;
			Info << endl;
		}
		size_t i = 0;
		for (const auto& x : myCurveMap)
		{
			const auto& c = x.second;


			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << c;

			if (verbose)
			{
				Info << " curve, " << x.first << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}
		if (verbose)
		{
			Info << endl;
			Info << " all curves have been saved, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	void printPoles()
	{
		checkFrame();
		const auto& poles = getScatterReg()->ScatterMap(SectPx_RegObjType::pole);
		Info << " nb. of poles: " << poles.size() << endl;
		Info << " the list of the poles: " << endl;
		for (const auto& x : poles)
		{
			auto p = std::dynamic_pointer_cast<SectPx_Pole>(x.second.lock());
			Debug_Null_Pointer(p);

			Info << " - " << "index: "
				<< p->Index() << ", "
				<< p->Name() << ", value: "
				<< p->Coord() << endl;
		}
	}

	void printCurves()
	{
		checkFrame();
		const auto& curves = getScatterReg()->ScatterMap(SectPx_RegObjType::curveQ);
		Info << " nb. of curves: " << curves.size() << endl;
		Info << " the list of the curves: " << endl;
		for (const auto& x : curves)
		{
			auto c = std::dynamic_pointer_cast<SectPx_CurveQ>(x.second.lock());
			Debug_Null_Pointer(c);

			Info << " - " << "index: " << c->Index() << ", " << c->Name() << endl;
			Info << "   from pole: "
				<< c->Pole0()->Index()
				<< ", to pole: " << c->Pole1()->Index()
				<< endl;
		}
	}

	//- create curves

	auto selectCurve(int id)
	{
		checkFrame();
		auto c = myCurveMaker->SelectCurve(id);
		return std::move(c);
	}

	void makeCurve(const std::shared_ptr<SectPx_CurveQ>& curveQ, int deg)
	{	
		checkFrame();
		if (verbose)
		{
			Info << endl;
			Info << " the curve with following specs are going to be created:" << endl;
			Info << " - index: " << curveQ->Index() << " , name: " << curveQ->Name() << endl;
			Info << " - degree: " << deg << endl;
		}

		if (verbose > 1)
		{
			Info << endl;
			Info << " retrieving the poles..." << endl;
		}
		const auto polesQ = SectPx_Tools::RetrievePoles(curveQ);
		if (verbose > 1)
		{
			Info << " - " << polesQ.size() << " nb. of poles have been retrieved" << endl;
			Info << endl;
		}

		if (verbose > 1)
		{
			Info << " retrieving the inner segments..." << endl;
		}
		const auto segments = SectPx_Tools::RetrieveInnerSegments(polesQ);

		if (verbose > 1)
		{
			Info << " retrieving the control points..." << endl;
		}
		const auto poles = SectPx_Tools::RetrieveControlPoints(segments);

		if (verbose > 1)
		{
			Info << " retrieving the knots..." << endl;
		}
		const auto knotsVect = SectPx_Tools::Knots(segments, std::min(4, std::max(1, deg)));
		const auto knots = SectPx_Tools::Knots(knotsVect);
		if (verbose > 2)
		{
			Info << " - knots vector: " << endl;
			Info << " ";
			for (auto x : knotsVect)
			{
				Info << "(" << x.first << ", " << x.second << ")" << ", ";
			}
			Info << endl;
		}

		if (verbose > 1)
		{
			Info << " retrieving the weights..." << endl;
		}
		const auto weights = SectPx_Tools::Weights(SectPx_Tools::RetrieveWeights(segments));
		if (verbose > 2)
		{
			Info << " - weights: " << endl;
			Info << " ";
			for (auto x : weights)
			{
				Info << x << ", ";
			}
			Info << endl;
		}
		const auto cpts = SectPx_Tools::CPts(poles);
		try
		{
			Handle(Geom2d_Curve) curve =
				new Geom2d_BSplineCurve(cpts, weights, knots.first, knots.second, deg);

			auto plnCurve = std::make_shared<Pln_Curve>(curveQ->Index(), std::move(curve));
			auto paired = std::make_pair(curveQ->Index(), std::move(plnCurve));
			auto insert = myCurveMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data" << endl
					<< abort(FatalError);
			}
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << endl;
			Info << " the geometric curve has been created, successfully!" << endl;
			Info << endl;
		}
	}

	void makeAllCurves()
	{
		const auto& curves = getScatterReg()->ScatterMap(SectPx_RegObjType::curveQ);
		for (const auto& x : curves)
		{
			auto c = std::dynamic_pointer_cast<SectPx_CurveQ>(x.second.lock());
			Debug_Null_Pointer(c);

			makeCurve(c, degree);
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadTuner(name); }), "loadTuner");
		mod->add(chaiscript::fun([]()->void {loadTuner(); }), "loadTuner");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([](unsigned short c)->void {setVerbose(c); }), "setVerbose");
	}

	void setCurves(const module_t& mod)
	{
		mod->add(chaiscript::fun([](int d)->void {degree = d; }), "setDegree");
		mod->add(chaiscript::fun([](int id)-> auto {auto t = selectCurve(id); return std::move(t); }), "selectCurve");
		mod->add(chaiscript::fun([](const std::shared_ptr<SectPx_CurveQ>& c, int deg)-> void {makeCurve(c, deg); }), "makeCurve");
		mod->add(chaiscript::fun([]()->void { makeAllCurves(); }), "makeAllCurves");
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
	//FatalError.throwExceptions();

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
			Info << "This application is aimed to create geometric curves." << endl;
			Info << endl
				<< " - the function are: " << endl << endl
				<< " - loadTuner(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " - printCurves()" << endl
				<< " - printPoles()" << endl
				<< endl
				<< " # settings: " << endl
				<< " - setVerbose(unsigned short);  levels: 0, 1" << endl << endl
				<< " - setDegree(n [integer])" << endl << endl

				<< " - operators: " << endl
				<< " - [CuvreQ] selectCurve(index)" << endl << endl
				<< " - makeCurve(CurveQ, n [integer])" << endl
				<< " - makeAllCurves()" << endl << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurves(mod);

			chai.add(mod);

			try
			{
				std::string address = ".\\system\\tnbPxModelSectionGeoCurveMaker";
				fileName myFileName(address);

				chai.eval_file(myFileName);
				return 0;
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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}
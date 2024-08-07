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
#include <SectPx_Pole.hxx>
#include <SectPx_RegObjType.hxx>
#include <SectPx_CurveQ.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <Geom2d_BSplineCurve.hxx>

#include <map>

namespace tnbLib
{

	static const std::string loadExt = SectPx_FrameTuner::extension;
	static const std::string saveExt = SectPx_FrameTuner::extension;

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static appl::tuner_t myTuner;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static std::string myFileName;

	static int degree = 3;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;

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

	/*void printPoles()
	{
		checkFrame();
		const auto& poles = getScatterReg()->ScatterMap(SectPx_RegObjType::pole);
		Info << endl;
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
		Info << endl;
	}*/

	void printCurves()
	{
		checkFrame();
		const auto& curves = getScatterReg()->ScatterMap(SectPx_RegObjType::curveQ);
		Info << endl;
		Info << " nb. of curves: " << curves.size() << endl;
		Info << " the list of the curves: " << endl;
		for (const auto& x : curves)
		{
			auto p = std::dynamic_pointer_cast<SectPx_CurveQ>(x.second.lock());
			Debug_Null_Pointer(p);

			Info << " - " << "index: "
				<< p->Index() << ", "
				<< p->Name() << endl;
		}
		Info << endl;
	}

	void printPoles()
	{
		const auto& poles = getScatterReg()->ScatterMap(SectPx_RegObjType::pole);
		Info << endl;
		Info << " Poles: " << endl;
		for (const auto& x : poles)
		{
			auto pole = std::dynamic_pointer_cast<SectPx_Pole>(x.second.lock());
			if (pole)
			{
				Info << " - " << "index: "
					<< pole->Index() << ", "
					<< pole->Name() << ", value: "
					<< pole->Coord() << ", point name: "
					<< pole->Pnt()->Name() << endl;
			}
		}
		Info << endl;
	}

	void printReg()
	{
		checkFrame();
		myTuner->PrintRegistry();
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

		if (verbose)
		{
			Info << endl;
			Info << " the curve maker is created, successfully!" << endl;
			Info << endl;
		}
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

		file::CheckExtension(name);

		fileName fn(name + saveExt);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myRegistry;
		oa << myTuner;

		if (verbose)
		{
			Info << endl;
			Info << " the tuner has been saved, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	//- curve maker

	auto selectBoundaryPole(int id)
	{
		auto t = myCurveMaker->SelectBoundary(id);
		return std::move(t);
	}

	auto selectSliderPole(int id)
	{
		auto t = myCurveMaker->SelectSlider(id);
		return std::move(t);
	}

	void createCurve(const appl::pole_t& p0, const appl::pole_t& p1)
	{
		myCurveMaker->CreateCurve(p0, p1);
	}

	void createCurve(const std::string& name, const appl::pole_t& p0, const appl::pole_t& p1)
	{
		myCurveMaker->CreateCurve(name, p0, p1);
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printReg(); }), "printRegistry");

		mod->add(chaiscript::fun([](unsigned short v)->void {setVerbose(v); }), "setVerbose");
	}

	void setCurvesMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](int id)-> auto {auto t = selectBoundaryPole(id); return std::move(t); }), "selectBoundaryPole");
		mod->add(chaiscript::fun([](int id)-> auto {auto t = selectSliderPole(id); return std::move(t); }), "selectSliderPole");
		mod->add(chaiscript::fun([](const appl::pole_t& p0, const appl::pole_t& p1)-> void {createCurve(p0, p1); }), "createCurve");
		mod->add(chaiscript::fun([](const std::string& name, const appl::pole_t& p0, const appl::pole_t& p1)-> void {createCurve(name, p0, p1); }), "createCurve");
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
			Info << endl;
			Info << " This application is aimed to create curve." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadTuner(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Global functions: " << endl << endl

				<< " - printRegistry()" << endl
				<< " - printPoles()" << endl
				<< " - printCurves()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Pole] selectBoundaryPole(index)" << endl
				<< " - [Pole] selectSliderPole(index)" << endl << endl

				<< " - createCurve(name [optional], Pole0, Pole1)" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurvesMakers(mod);

			chai.add(mod);	

			try
			{
				std::string address = ".\\system\\tnbPxModelSectionCurveMaker";
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}
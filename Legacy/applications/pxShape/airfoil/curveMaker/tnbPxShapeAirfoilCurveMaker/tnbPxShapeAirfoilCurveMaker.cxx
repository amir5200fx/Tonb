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
#include <SectPx_Node.hxx>
#include <SectPxIO_Airfoil.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>
#include <Global_File.hxx>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <Geom2d_BSplineCurve.hxx>

#include <map>

namespace tnbLib
{

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static appl::frame_t myFrame;
	static appl::tuner_t myTuner;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static int degree = 3;
	static std::string myFileName;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;


	static std::vector<appl::profileMaker_t> myThickness;
	static std::vector<appl::profileMaker_t> myCamber;

	static std::shared_ptr<SectPxIO_Airfoil> myAirfoil;

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

	void printPoles()
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
	}

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

	void printReg()
	{
		checkFrame();
		myTuner->PrintRegistry();
	}

	void loadFile(const std::string& name)
	{
		myFileName = name;
		file::CheckExtension(name);
		myAirfoil = file::LoadFile<std::shared_ptr<SectPxIO_Airfoil>>(name + SectPxIO_Airfoil::extension, verbose);
		if (NOT myAirfoil)
		{
			FatalErrorIn(FunctionSIG)
				<< " the airfoil file is null." << endl
				<< abort(FatalError);
		}

		myRegistry = myAirfoil->Registry();
		if (NOT myRegistry)
		{
			FatalErrorIn(FunctionSIG)
				<< " the registry is null" << endl
				<< abort(FatalError);
		}
		if (myRegistry->NbFrames() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< " it's not a valid registry" << endl
				<< abort(FatalError);
		}

		myFrame = myAirfoil->Frame();
		if (NOT myFrame)
		{
			FatalErrorIn(FunctionSIG)
				<< " the frame registry is null" << endl
				<< abort(FatalError);
		}
		if (NOT myFrame->FrameRegistry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no registry has been detected for the frame" << endl
				<< abort(FatalError);
		}

		myCamber = myAirfoil->Camber();
		myThickness = myAirfoil->Thickness();

		if (NOT myCamber.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "no camber profile has been detected!" << endl
				<< abort(FatalError);
		}

		if (NOT myThickness.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "no thickness profile has been detected!" << endl
				<< abort(FatalError);
		}

		myTuner = myAirfoil->Tuner();
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

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), SectPxIO_Airfoil::extension).string();
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		file::CheckExtension(name);
		file::SaveTo(myAirfoil, name + SectPxIO_Airfoil::extension, verbose);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printReg(); }), "printRegistry");

		mod->add(chaiscript::fun([](unsigned short v)->void {verbose = v; }), "setVerbose");
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

int main(int argc, char* argv[])
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurvesMakers(mod);

			chai.add(mod);

			auto address = file::GetSystemFile("tnbPxShapeAirfoilCurveMaker");
			fileName myFileName(address);

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
	return 0;
}
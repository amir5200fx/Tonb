#include <Pln_Curve.hxx>
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

	static appl::tuner_t myTuner;

	static bool verbose = false;
	static bool loaded = false;
	static int degree = 3;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;

	//- globals

	void checkFrame()
	{
		if (NOT loaded)
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

	void printReg()
	{
		checkFrame();
		myTuner->PrintRegistry();
	}

	void loadTuner(const std::string& name)
	{

		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive ia(f);

		ia >> myTuner;

		if (verbose)
		{
			Info << " the tuner has been loaded successfully!" << endl;
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
		loaded = true;
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myTuner;

		if (verbose)
		{
			Info << " the tuner has been saved, successfully!" << endl;
		}
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTunerTo");

		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([]()->void {printReg(); }), "printRegistry");

		mod->add(chaiscript::fun([](bool v)->void {verbose = v; }), "setVerbose");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurvesMakers(mod);

			chai.add(mod);

			fileName myFileName("sectionCurveMaker");

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
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
#include <SectPx_CurveQ.hxx>
#include <SectPx_Pole.hxx>
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

	static appl::tuner_t myTuner;

	static bool verbose = false;
	static bool loaded = false;
	static int degree = 3;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;
	static std::map<int, std::shared_ptr<Pln_Curve>> myCurveMap;

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

	void saveCurvesTo(const std::string& name)
	{
		if (verbose)
		{
			Info << " nb. of curves going to be saved: " << myCurveMap.size() << endl;
		}
		size_t i = 0;
		for (const auto& x : myCurveMap)
		{
			const auto& c = x.second;

			
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << c;

			if (verbose)
			{
				Info << " curve, " << x.first << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}
	}

	//- create curves

	auto selectCurve(int id)
	{
		checkFrame();
		auto c = myCurveMaker->SelectCurve(id);
		return std::move(c);
	}

	void makeCurve(const std::shared_ptr<SectPx_CurveQ>& curveQ)
	{
		checkFrame();
		const auto polesQ = SectPx_Tools::RetrievePoles(curveQ);
		const auto segments = SectPx_Tools::RetrieveInnerSegments(polesQ);
		const auto poles = SectPx_Tools::RetrieveControlPoints(segments);

		const auto knots = SectPx_Tools::Knots(SectPx_Tools::Knots(segments, std::min(3, std::max(2, degree))));
		const auto weights = SectPx_Tools::Weights(SectPx_Tools::RetrieveWeights(segments));
		const auto cpts = SectPx_Tools::CPts(poles);

		try
		{
			Handle(Geom2d_Curve) curve = 
				new Geom2d_BSplineCurve(cpts, weights, knots.first, knots.second, degree);

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
	}

	void makeAllCurves()
	{
		const auto& curves = getScatterReg()->ScatterMap(SectPx_RegObjType::curveQ);
		for (const auto& x : curves)
		{
			auto c = std::dynamic_pointer_cast<SectPx_CurveQ>(x.second.lock());
			Debug_Null_Pointer(c);

			makeCurve(c);
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
		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([](bool c)->void {verbose = c; }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)->void {saveCurvesTo(name); }), "saveAllTo");
	}

	void setCurves(const module_t& mod)
	{
		mod->add(chaiscript::fun([](int d)->void {degree = d; }), "setDegree");
		mod->add(chaiscript::fun([](int id)-> auto {auto t = selectCurve(id); return std::move(t); }), "selectCurve");
		mod->add(chaiscript::fun([](const std::shared_ptr<SectPx_CurveQ>& c)-> void {makeCurve(c); }), "makeCurve");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurves(mod);

			chai.add(mod);

			fileName myFileName("sectionGeoCurveMaker");

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
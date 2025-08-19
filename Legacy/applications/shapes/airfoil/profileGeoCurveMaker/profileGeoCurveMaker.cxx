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
#include <vector>

namespace tnbLib
{

	static appl::tuner_t myTuner;

	static unsigned short verbose = 0;
	static bool loaded = false;
	static int degree = 3;

	static std::shared_ptr<SectPx_Registry> myRegistry;
	static std::shared_ptr<maker::CurveQ> myCurveMaker;
	static std::map<int, std::shared_ptr<Pln_Curve>> myCurveMap;


	static std::vector<appl::profileMaker_t> myThickness;
	static std::vector<appl::profileMaker_t> myCamber;

	enum class matter
	{
		camber,
		thickness
	};

	static std::map<matter, std::vector<int>> myCurveMatterMap;

	static std::map<appl::profile_t, matter> profileMatter;

	//- globals

	void setMatter(matter t, int i)
	{
		auto iter = myCurveMatterMap.find(t);
		if (iter IS_EQUAL myCurveMatterMap.end())
		{
			auto list = std::vector<int>();
			list.push_back(i);
			auto paired = std::make_pair(t, std::move(list));
			auto insert = myCurveMatterMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto& list = iter->second;
			list.push_back(i);
		}
	}

	void registerMatters(const std::vector<appl::profileMaker_t>& profiles, matter m)
	{
		for (const auto& x : profiles)
		{
			const auto& t = x->TopoProfile();
			auto paired = std::make_pair(t, m);
			auto insert = profileMatter.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
	}

	matter retrieveMatter(const appl::pole_t& p)
	{
		auto prf = p->TopoProfile().lock();
		Debug_Null_Pointer(prf);

		auto iter = profileMatter.find(prf);
		if (iter IS_EQUAL profileMatter.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "unidentified profile has been detected!" << endl
				<< abort(FatalError);
		}

		auto m = iter->second;
		return m;
	}

	auto checkCurve(const std::shared_ptr<SectPx_CurveQ>& curve)
	{
		auto m0 = retrieveMatter(curve->Pole0());
		auto m1 = retrieveMatter(curve->Pole1());
		if (m0 NOT_EQUAL m1)
		{
			FatalErrorIn(FunctionSIG)
				<< "Unmatched profile type for a curve has been detected!" << endl
				<< abort(FatalError);
		}
		return m0;
	}

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

		ia >> myCamber;
		ia >> myThickness;

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

		registerMatters(myCamber, matter::camber);
		registerMatters(myThickness, matter::thickness);

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
			Info << endl;
			Info << " nb. of curves are going to be saved: " << myCurveMap.size() << endl;
			Info << endl;
		}

		{
			const auto& curvesIds = myCurveMatterMap[matter::camber];

			std::vector<std::shared_ptr<Pln_Curve>> curves;
			curves.reserve(curvesIds.size());

			for (auto id : curvesIds)
			{
				auto iter = myCurveMap.find(id);
				if (iter IS_EQUAL myCurveMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "couldn't find the item" << endl
						<< abort(FatalError);
				}
				curves.push_back(iter->second);
			}

			std::string address = ".\\camber\\" + name;
			boost::filesystem::path dir("camber");
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << curves;

			Info << " camber profile is saved in: " << address << ", successfully!" << endl;
		}

		{
			const auto& curvesIds = myCurveMatterMap[matter::thickness];

			std::vector<std::shared_ptr<Pln_Curve>> curves;
			curves.reserve(curvesIds.size());

			for (auto id : curvesIds)
			{
				auto iter = myCurveMap.find(id);
				if (iter IS_EQUAL myCurveMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "couldn't find the item" << endl
						<< abort(FatalError);
				}
				curves.push_back(iter->second);
			}

			std::string address = ".\\thickness\\" + name;
			boost::filesystem::path dir("thickness");
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << curves;

			Info << " thickness profile is saved in: " << address << ", successfully!" << endl;
		}

		if (verbose)
		{
			Info << endl;
			Info << " all curves have been saved, successfully!" << endl;
			Info << endl;
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
		auto mat = checkCurve(curveQ);
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
		const auto knotsVect = SectPx_Tools::Knots(segments, std::min(3, std::max(1, deg)));
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
			setMatter(mat, curveQ->Index());
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
		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printPoles(); }), "printPoles");
		mod->add(chaiscript::fun([](unsigned short c)->void {verbose = c; }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)->void {saveCurvesTo(name); }), "saveAllTo");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setCurves(mod);

			chai.add(mod);

			fileName myFileName("profileGeoCurveMaker");

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
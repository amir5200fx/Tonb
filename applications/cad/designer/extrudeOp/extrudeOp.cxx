#include <ShapePx_Section.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_ExtrudeOp.hxx>
#include <ShapePx_Spacing.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_TopoCtrlNet.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_CurveQ.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_Spacing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	typedef std::shared_ptr<ShapePx_ExtrudedPatch> patch_t;
	typedef std::shared_ptr<SectPx_Spacing> spacing_t;
	typedef std::shared_ptr<SectPx_CurveQ> curve_t;
	typedef std::shared_ptr<ShapePx_TopoCtrlNet> net_t;

	static patch_t myPatch;
	//static spacing_t mySpacing;
	static std::vector<spacing_t> mySpacings;

	static unsigned short verbose = 0;

	static std::string spacingDir = "spacing";
	static std::string patchDir = "patch";

	static std::vector<net_t> myNets;

	static std::vector<std::pair<curve_t, spacing_t>> pairs;
	static std::vector<curve_t> myCurves;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;
	static std::shared_ptr<maker::Spacing> mySpacingMaker;

	static bool loadTag = false;

	static std::map<int, int> degreeMap;

	void checkLoad()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no patch is loaded, yet!" << endl
				<< abort(FatalError);
		}
	}

	void loadSpacing(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "couldn't open the file: " << fn << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);

		std::shared_ptr<ShapePx_Patch> patch;
		ia >> patch;
		//ia >> mySpacings;

		myPatch = std::dynamic_pointer_cast<ShapePx_ExtrudedPatch>(patch);

		if (NOT myPatch)
		{
			FatalErrorIn(FunctionSIG)
				<< "the patch is null" << endl
				<< abort(FatalError);
		}

		if (NOT myPatch->Section())
		{
			FatalErrorIn(FunctionSIG)
				<< " no section has been found in the patch!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the patch has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}

		/*if (verbose)
		{
			Info << endl;
			Info << " the spacing list has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}*/

		myCurves = myPatch->Section()->RetrieveCurveQs();
		if (myCurves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< " no curve has been defined in the section!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " " << myCurves.size() << " nb. of curves has been detected!" << endl;
		}

		mySpacingMaker = std::make_shared<maker::Spacing>(myPatch->Registry()->Shape());
		myCurveMaker = std::make_shared<maker::CurveQ>(myPatch->Section()->Registry());

		loadTag = true;
	}

	auto selectCurve(int i)
	{
		checkLoad();
		auto t = myCurveMaker->SelectCurve(i);
		return std::move(t);
	}

	auto selectSpacing(int i)
	{
		checkLoad();
		auto t = mySpacingMaker->SelectSpacing(i);
		return std::move(t);
	}

	void makePair(const curve_t& curve, const spacing_t& space, int degree)
	{
		checkLoad();
		auto paired = std::make_pair(curve, space);
		pairs.push_back(std::move(paired));

		degreeMap.insert(std::make_pair(curve->Index(), degree));
	}

	void execute()
	{
		checkLoad();
		for (const auto& x : pairs)
		{
			auto op = std::make_shared<ShapePx_ExtrudeOp>();

			op->SetCurve(x.first);
			op->SetSpacing(x.second);
			op->SetPatch(myPatch);

			auto deg = degreeMap[x.first->Index()];
			op->SetDegreeU(deg);

			op->Perform();

			myNets.push_back(op->Net());
		}

		if (verbose)
		{
			Info << endl;
			Info << " the control nets are created, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		checkLoad();
		if (verbose)
		{
			Info << endl;
			Info << " " << myNets.size() << " nb. of curves is going to be saved." << endl;
			Info << endl;
		}

		size_t i = 0;
		for (const auto& x : myNets)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << x;

			if (verbose)
			{
				Info << " net, " << i << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}
	}

	void printObj(const std::shared_ptr<SectPx_RegObj>& item)
	{
		Info << "- index: " << item->Index()
			<< ", " << getRegObjTypeName(item->RegObjType())
			<< "'s name: "
			<< "["
			<< item->Name()
			<< "]"
			<< endl;
	}

	void printReg()
	{
		checkLoad();
		const auto& scatterReg = myPatch->Registry()->Scatter();
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::parameter))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " field functions: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::fieldFun))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " points: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::pnt))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " edges: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::edge))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " profiles: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::profile))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " nodes: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::node))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " datums: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::datum))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " geometric maps: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::geoMap))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " interfaces: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::Interface))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " poles: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::pole))
		{
			auto item = x.second.lock();
			printObj(item);
		}
		Info << endl;
		Info << " segments: " << endl;
		Info << endl;
		for (const auto& x : scatterReg->ScatterMap(SectPx_RegObjType::segment))
		{
			auto item = x.second.lock();
			printObj(item);
		}

		const auto curves = scatterReg->ScatterMap(SectPx_RegObjType::curveQ);
		if (curves.size())
		{
			Info << endl;
			Info << " curves: " << endl;
			Info << endl;
			for (const auto& x : curves)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto limits = scatterReg->ScatterMap(SectPx_RegObjType::limits);
		if (limits.size())
		{
			Info << endl;
			Info << " limits: " << endl;
			Info << endl;
			for (const auto& x : limits)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto extrProfiles = scatterReg->ScatterMap(SectPx_RegObjType::extrProfile);
		if (extrProfiles.size())
		{
			Info << endl;
			Info << " extrProfiles: " << endl;
			Info << endl;
			for (const auto& x : extrProfiles)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}

		const auto spacings = scatterReg->ScatterMap(SectPx_RegObjType::spacing);
		if (spacings.size())
		{
			Info << endl;
			Info << " spacings: " << endl;
			Info << endl;
			for (const auto& x : spacings)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}
	}

	void printCurves()
	{
		checkLoad();
		const auto& scatterReg = myPatch->Registry()->Scatter();
		const auto curves = scatterReg->ScatterMap(SectPx_RegObjType::curveQ);
		if (curves.size())
		{
			Info << endl;
			Info << " curves: " << endl;
			Info << endl;
			for (const auto& x : curves)
			{
				auto item = x.second.lock();
				printObj(item);
			}
		}
	}

	void printSpacings()
	{
		checkLoad();
		const auto& scatterReg = myPatch->Registry()->Scatter();
		const auto spacings = scatterReg->ScatterMap(SectPx_RegObjType::spacing);
		if (spacings.size())
		{
			Info << endl;
			Info << " spacings: " << endl;
			Info << endl;
			for (const auto& x : spacings)
			{
				auto item = x.second.lock();
				printObj(item);
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadSpacing(name); }), "loadPatch");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {printCurves(); }), "printCurves");
		mod->add(chaiscript::fun([]()->void {printSpacings(); }), "printSpacings");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		mod->add(chaiscript::fun([](int i)-> auto{return selectCurve(i); }), "selectCurve");
		mod->add(chaiscript::fun([](int i)-> auto{return selectSpacing(i); }), "selectSpacing");

		mod->add(chaiscript::fun([](const curve_t& c, const spacing_t& s, int deg)-> void {makePair(c, s, deg); }), "makePair");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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

			chai.add(mod);

			fileName myFileName("TnbExtrudeOp");

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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
		/*else if (IsEqualCommand(argv[1], "--flush"))
		{
			try
			{
				flushDirs();
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}*/
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}
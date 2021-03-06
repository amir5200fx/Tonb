#include <ShapePx_UniformSpacing.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_Section.hxx>
#include <SectPx_LimitsMaker.hxx>
#include <SectPx_SpacingMaker.hxx>
#include <SectPx_Limits.hxx>
#include <SectPx_ParameterMaker.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_ShapeRegistry.hxx>
#include <SectPx_UniformSpacing.hxx>
#include <SectPx_Pars.hxx>
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

namespace tnbLib
{

	typedef std::shared_ptr<ShapePx_Spacing> spacing_t;
	typedef std::shared_ptr<SectPx_Limits> limits_t;
	typedef std::shared_ptr<maker::Limits> limitMaker_t;
	typedef std::shared_ptr<maker::Spacing> spacingMaker_t;
	typedef std::shared_ptr<ShapePx_ExtrudedPatch> patch_t;

	static std::vector<spacing_t> mySpacings;
	static patch_t myPatch;

	static std::shared_ptr<maker::Parameter> myParMaker;

	static unsigned short verbose = 0;

	static limitMaker_t myLimitMaker;
	static spacingMaker_t mySpacingMaker;

	static bool loadTag = false;

	void checkLoad()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no patch is loaded, yet!" << endl
				<< abort(FatalError);
		}
	}

	auto makeLimits(const appl::par_t& x0, const appl::par_t& x1)
	{
		checkLoad();
		auto t = myLimitMaker->SelectLimits(myLimitMaker->CreateLimits(x0, x1));
		return std::move(t);
	}

	auto makeUniformSpacing(const limits_t& l, const Standard_Integer n)
	{
		auto t = mySpacingMaker->SelectSpacing(mySpacingMaker->CreateUniform(l, n));
		return std::move(t);
	}

	void loadPatch(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the patch..." << endl;
			Info << endl;
		}

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

		myPatch = std::dynamic_pointer_cast<ShapePx_ExtrudedPatch>(patch);

		if (NOT myPatch)
		{
			FatalErrorIn(FunctionSIG)
				<< "the patch is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the patch has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}

		myParMaker = std::make_shared<maker::Parameter>(myPatch->Registry()->Parameter());
		myLimitMaker = std::make_shared<maker::Limits>(myPatch->Registry()->Shape());
		mySpacingMaker = std::make_shared<maker::Spacing>(myPatch->Registry()->Shape());

		if (verbose)
		{
			Info << endl;
			Info << " the parameter maker is created, successfully!" << endl;
			Info << " the limits maker is created, successfully!" << endl;
			Info << endl;
		}

		loadTag = true;
	}

	auto selectParameter(int i)
	{
		checkLoad();
		auto item = myParMaker->SelectParameter(i);
		return std::move(item);
	}

	void saveTo(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " " << mySpacings.size() << " nb. of spacing is going to be saved." << endl;
			Info << endl;
		}

		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		std::shared_ptr<ShapePx_Patch> patch = myPatch;
		oa << patch;
		//oa << mySpacings;

		if (verbose)
		{
			Info << endl;
			Info << " the spacings are saved to the patch, successfully!" << endl;
			Info << " - filename: " << fn << endl;
			Info << endl;
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

	void printSectionParameters()
	{
		checkLoad();
		const auto& section = myPatch->Section();
		if (NOT section)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section is found for the patch!" << endl
				<< abort(FatalError);
		}
		const auto parameters = section->RetrieveParameters();
		Info << endl;
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			printObj(x);
		}
	}

	void printFixedSectionParameters()
	{
		checkLoad();
		const auto& section = myPatch->Section();
		if (NOT section)
		{
			FatalErrorIn(FunctionSIG)
				<< "no section is found for the patch!" << endl
				<< abort(FatalError);
		}
		const auto parameters = section->RetrieveParameters();
		Info << endl;
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			auto p = std::dynamic_pointer_cast<SectPx_FixedPar>(x);
			if (p)
			{
				printObj(x);
			}			
		}
	}

	void printFixedGlobalParameters()
	{
		checkLoad();
		const auto& shape = myPatch->Registry()->Shape();
		const auto parameters = shape->RetrieveGlobalParameters();
		Info << endl;
		Info << " fixed parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			auto p = std::dynamic_pointer_cast<SectPx_FixedPar>(x);
			if (p)
			{
				printObj(x);
			}
		}
	}

	void printGlobalParameters()
	{
		checkLoad();
		const auto& shape = myPatch->Registry()->Shape();
		const auto parameters = shape->RetrieveGlobalParameters();
		Info << endl;
		Info << " parameters: " << endl;
		Info << endl;
		for (const auto& x : parameters)
		{
			printObj(x);
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadPatch(name); }), "loadPatch");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {printReg(); }), "printRegistry");
		mod->add(chaiscript::fun([]()->void {printSectionParameters(); }), "printSectionPars");
		mod->add(chaiscript::fun([]()->void {printFixedSectionParameters(); }), "printFixedSectionPars");
		mod->add(chaiscript::fun([]()->void {printGlobalParameters(); }), "printGlobalPars");
		mod->add(chaiscript::fun([]()->void {printFixedGlobalParameters(); }), "printFixedGlobalPars");

		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");

		mod->add(chaiscript::fun([](int i)-> auto{auto t = selectParameter(i); return std::move(t); }), "selectParameter");

		mod->add(chaiscript::fun([](const appl::par_t& x0, const appl::par_t& x1)->auto {auto t = makeLimits(x0, x1); return std::move(t); }), "createLimits");

		mod->add(chaiscript::fun([](const limits_t& l, int n)-> auto {auto t = makeUniformSpacing(l, n); return std::move(t); }), "createUniform");
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

			fileName myFileName("TnbShapeSpacing");

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
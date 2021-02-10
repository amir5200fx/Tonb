#include <ShapePx_Section.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Par.hxx>
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

	typedef std::shared_ptr<ShapePx_Patch> patch_t;
	typedef std::shared_ptr<ShapePx_Section> section_t;
	typedef std::shared_ptr<SectPx_Registry> registry_t;

	static patch_t myPatch;

	static section_t mySection;
	static registry_t myRegistry;
	
	static std::map<int, appl::par_t> sectionPars;

	static unsigned short verbose = 0;

	void loadSection(const std::string& name)
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
		ia >> myRegistry;
		ia >> mySection;
		//ia >> sectionPars;

		if (NOT myRegistry)
		{
			FatalErrorIn(FunctionSIG)
				<< " the registry is null" << endl
				<< abort(FatalError);
		}

		if (NOT mySection)
		{
			FatalErrorIn(FunctionSIG)
				<< " the section is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the section has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void makeExtrPatch(const std::string& name)
	{
		if (NOT mySection)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no section has been loaded!" << endl
				<< abort(FatalError);
		}

		myPatch = std::make_shared<ShapePx_ExtrudedPatch>(myRegistry, mySection);
		myPatch->SetName(name);

		if (verbose)
		{
			Info << endl;
			Info << " the patch has been created, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT myPatch)
		{
			FatalErrorIn(FunctionSIG)
				<< " no patch has been created!" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);
		oa << myPatch;

		if (verbose)
		{
			Info << endl;
			Info << " the patch is saved to: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadSection(name); }), "loadSection");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](const std::string& name)-> void {makeExtrPatch(name); }), "makeExtrPatch");
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
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

			fileName myFileName("TnbShapePatch");

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
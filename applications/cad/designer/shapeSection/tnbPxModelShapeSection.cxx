#include <ShapePx_Section.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Par.hxx>
#include <Global_File.hxx>
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

	static const std::string loadExt = SectPx_FrameTuner::extension;
	static const std::string saveExt = ShapePx_Section::extension;

	typedef std::shared_ptr<SectPx_Registry> registry_t;
	typedef std::shared_ptr<ShapePx_Section> section_t;
	typedef std::shared_ptr<SectPx_FrameTuner> tuner_t;

	static tuner_t myTuner;
	static section_t mySection;
	static registry_t myRegistry;

	static std::map<int, appl::par_t> sectionPars;

	static unsigned short verbose = 0;

	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadTuner(const std::string& name)
	{
		file::CheckExtension(name);

		fileName fn(name + loadExt);
		std::ifstream f(fn);

		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "couldn't open the file: " << fn << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);
		ia >> myRegistry;
		ia >> myTuner;

		if (NOT myRegistry)
		{
			FatalErrorIn(FunctionSIG)
				<< " the registry is null" << endl
				<< abort(FatalError);
		}
		
		if (NOT myTuner)
		{
			FatalErrorIn(FunctionSIG)
				<< " the tuner is null" << endl
				<< abort(FatalError);
		}

		const auto& curves = myTuner->FrameRegistry()->Scatter()->ScatterMap(SectPx_RegObjType::curveQ);
		if (curves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< " no curve has been defined for this section!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the tuner has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}

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
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no section has been created!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		fileName fn(name + saveExt);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);
		oa << myRegistry;
		oa << mySection;
		//oa << sectionPars;

		if (verbose)
		{
			Info << endl;
			Info << " the section is saved to: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	void makeSection(const std::string& name)
	{
		if (NOT myTuner)
		{
			FatalErrorIn(FunctionSIG)
				<< "no tuner has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		mySection = std::make_shared<ShapePx_Section>(0, name, myTuner->FrameRegistry());

		/*auto pars = mySection->RetrieveParameters();
		for (const auto& x : pars)
		{
			auto paired = std::make_pair(x->Index(), x);
			auto insert = sectionPars.insert(std::move(paired));

			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}*/
		if (verbose)
		{
			Info << endl;
			Info << " the section of the shape has been created, successfully!" << endl;
			Info << endl;
		}

		exeTag = true;
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {makeSection(name); }), "execute");
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
			Info << "This application is aimed to create a shape section." << endl;
			Info << endl
				<< " - the function are: " << endl << endl
				<< " - loadTuner(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " - execute(name)" << endl
				<< endl
				<< " # settings: " << endl
				<< " - setVerbose(unsigned short);  levels: 0, 1" << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				std::string address = ".\\system\\tnbPxModelShapeSection";
				fileName theFileName(address);

				chai.eval_file(theFileName);
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
#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Geo_ProfileFun.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static const std::string saveExt = Marine_Model::extension;
	static const std::string loadExt = Geo_ProfileFun::extension;

	static std::string currentPath;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose = 0;

	static std::shared_ptr<Marine_Model> myModel;

	static std::shared_ptr<Geo_ProfileFun> myAreaProfile;
	static std::shared_ptr<Geo_ProfileFun> myZBarProfile;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadProfiles()
	{
		if (verbose)
		{
			Info << "loading the profiles..." << endl;
			Info << endl;
		}

		{
			const std::string folder = "area";
			auto dir = boost::filesystem::path(currentPath + R"(\)" + folder);

			//- change the current path
			boost::filesystem::current_path(dir);
			auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();

			myAreaProfile = file::LoadFile<std::shared_ptr<Geo_ProfileFun>>(name + loadExt, verbose);
			if (NOT myAreaProfile)
			{
				FatalErrorIn(FunctionSIG)
					<< "the profile is null!" << endl
					<< abort(FatalError);
			}
		}

		{
			const std::string folder = "zbar";
			auto dir = boost::filesystem::path(currentPath + R"(\)" + folder);

			//- change the current path
			boost::filesystem::current_path(dir);
			auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();

			myAreaProfile = file::LoadFile<std::shared_ptr<Geo_ProfileFun>>(name + loadExt, verbose);
			if (NOT myAreaProfile)
			{
				FatalErrorIn(FunctionSIG)
					<< "the profile is null!" << endl
					<< abort(FatalError);
			}
		}

		if (verbose)
		{
			Info << endl
				<< " All files are loaded, successfully!" << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << myModel;

		if (verbose)
		{
			Info << endl;
			Info << " the model is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded, yet!" << endl
				<< abort(FatalError);
		}
		boost::filesystem::current_path(currentPath);

		myModel = std::make_shared<marineLib::Model_ProfileAreaSail>(0, name, myAreaProfile, myZBarProfile);

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< "the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("");
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
		mod->add(chaiscript::fun([]()->void {loadProfiles(); }), "loadProfiles");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute");
	
		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
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
	FatalError.throwExceptions();

	currentPath = boost::filesystem::current_path().string();

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
			Info << " This application is aimed to create a model sail from the area and the z-bar profiles." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadProfiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				//std::string address = ".\\system\\tnbHydstcProfileAreaSailModelMaker";
				fileName myFileName(file::GetSystemFile("tnbHydstcProfileAreaSailModelMaker"));

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
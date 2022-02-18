#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::string loadExt = Entity2d_Triangulation::extension;
	static std::string saveExt = Entity2d_Triangulation::extension + "list";

	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myEntities;

	static bool verbose = false;
	static bool loadTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFiles()
	{
		auto currentPath = boost::filesystem::current_path().string();
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto name = file::GetSingleFile(currentPath + std::to_string(i), loadExt).string();
				file::CheckExtension(name);

				auto ent = file::LoadFile<std::shared_ptr<Entity2d_Triangulation>>(name + loadExt, verbose);

				myEntities.push_back(std::move(ent));

				i++;
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - " << myEntities.size()
				<< " meshes are loaded successfully in "
				<< global_time_duration
				<< " ms."
				<< endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been loaded." << endl
				<< abort(FatalError);
		}
		file::SaveTo(myEntities, name + saveExt, verbose);
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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
			Info << " This application is aimed to load meshes and putting them into a list." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshList2d"));

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
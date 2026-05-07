#include <Cad_MultiVolume.hxx>
#include <Cad_SingleVolume.hxx>
#include <Cad_Solid.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose = 0;

	static std::vector<std::shared_ptr<Cad_Solid>> mySolids;
	static std::shared_ptr<Cad_Volume> myVolume;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFiles()
	{
		if (verbose)
		{
			Info << " loading the files..." << endl
				<< endl;
		}

		{
			Global_Timer myTimer;
			myTimer.SetInfo(Global_TimerInfo_ms);

			const auto currentPath = boost::filesystem::current_path();

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto dir = boost::filesystem::path(currentPath.string() + R"(\)" + std::to_string(i));

				//- change the current path
				boost::filesystem::current_path(dir);

				auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_TModel::extension).string();
				file::CheckExtension(name);

				auto myModel = file::LoadFile<std::shared_ptr<Cad_TModel>>(name + Cad_TModel::extension, verbose);
				if (auto mySolid = std::dynamic_pointer_cast<Cad_Solid>(myModel))
				{
					mySolids.push_back(std::move(mySolid));
				}
				else
				{
					Info << endl
						<< "- WARNING! the object is not a solid." << endl;
				}
				++i;
				boost::filesystem::current_path(currentPath);
			}

			//- change back the current path
			boost::filesystem::current_path(currentPath);
		}

		if (verbose)
		{
			Info << endl
				<< " - All models are loaded, in: " << global_time_duration << " ms." << endl;
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

		file::CheckExtension(name);

		file::SaveTo(myVolume, name + Cad_Volume::extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myVolume->Name());
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl
				<< " - no. of solids = " << mySolids.size() << endl;
		}
		myVolume = std::make_shared<Cad_MultiVolume>(0, name, mySolids);

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " the application is successfully performed!" << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}
		execute("myVol");
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
		// io functions [8/1/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// settings [8/1/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to create a multi volume." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Operators: " << endl << endl

				<< " - execute(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbCadToolMultiVol");
				fileName myFileName(address);

				chai.eval_file(myFileName);
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}
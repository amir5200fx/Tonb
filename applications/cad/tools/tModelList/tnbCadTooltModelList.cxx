#include <Cad_TModel.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	static bool loadTag = false;
	static unsigned short verbose = 0;
	static const std::string extension = Cad_TModel::extension;

	static std::vector<std::shared_ptr<Cad_TModel>> myModels;

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
				myModels.push_back(std::move(myModel));
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
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myModels, name + extension + "list", verbose);
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

		// settings [8/1/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
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
			Info << " This application is aimed to create a model list." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

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
				auto address = file::GetSystemFile("tnbCadTooltModelList");
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
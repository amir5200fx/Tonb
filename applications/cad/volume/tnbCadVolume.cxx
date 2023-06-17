#include <Cad_SingleVolume.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Solid.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Cad_TModel> myModel;
	static std::shared_ptr<Cad_Volume> myVolume;

	static std::string myFileName;

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;

	static const auto model_directory = "model";

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel()
	{
		myModel = file::LoadSingleFile<std::shared_ptr<Cad_TModel>>
			(
				model_directory,
				Cad_TModel::extension,
				verbose, 
				myFileName
				);
		loadTag = true;
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadModelFile(const std::string& name)
	{
		file::CheckExtension(name);
		myModel = 
			file::LoadFile<std::shared_ptr<Cad_TModel>>
			(name + Cad_TModel::extension, verbose);
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
		loadTag = true;
		myFileName = name;
	}

	void loadFile()
	{
		if (file::IsDirectory(model_directory))
		{
			loadModel();
		}
		else
		{
			auto name = 
				file::GetSingleFile
				
				(boost::filesystem::current_path(),
					Cad_TModel::extension
				).string();	
			loadModelFile(name);
		}
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
		saveTo(myFileName);
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		if (auto solid = std::dynamic_pointer_cast<Cad_Solid>(myModel))
		{
			myVolume = std::make_shared<Cad_SingleVolume>(0, name, std::move(solid));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is not solid." << endl
				<< abort(FatalError);
		}
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		execute(myModel->Name());
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions 
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModelFile(name); }), "loadFile");

		// settings 
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators 
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
	FatalConvError.throwExceptions();

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
			Info << " This application is aimed to create a volume." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadVolume"));

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
#include <Cad_MultiVolume.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;

	static const auto model_directory = "model";

	static std::shared_ptr<Cad_Volume> my_model;
	static std::shared_ptr<Cad_MultiVolume> multi_volume;

	TNB_SET_VERBOSE_FUN;

	void loadModel()
	{
		my_model = file::LoadSingleFile<std::shared_ptr<Cad_Volume>>(model_directory, Cad_Volume::extension, verbose, myFileName);
		if (NOT my_model)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " no model has been loaded." << endl
				<< abort(FatalError);
		}
		multi_volume = std::dynamic_pointer_cast<Cad_MultiVolume>(my_model);
		if (NOT multi_volume)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "it's a singular volume." << endl
				<< abort(FatalError);
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);
		my_model = file::LoadFile<std::shared_ptr<Cad_Volume>>(name + Cad_Volume::extension, verbose);
		if (NOT my_model)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
		myFileName = name;
		multi_volume = std::dynamic_pointer_cast<Cad_MultiVolume>(my_model);
		if (NOT multi_volume)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "it's a singular volume." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		if (file::IsDirectory(model_directory))
		{
			loadModel();
		}
		else
		{
			const auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Volume::extension).string();
			loadFile(name);
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
		file::SaveTo(my_model, name + Cad_Volume::extension, verbose);
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	void setPair(int s0, int s1)
	{
		if (NOT my_model)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
		multi_volume->SetPairs(Cad_MultiVolume::PairedEntity{s0, s1});
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
		// io functions [1/31/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// operators [1/31/2022 Amir]
		mod->add(chaiscript::fun([](int s0, int s1)-> void {setPair(s0, s1); }), "setPair");

		// settings [1/31/2022 Amir]
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

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();
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
			Info << " This application is aimed to set paired surfaces on a multi-volume solids." << endl << endl;

			Info << " You can load the solid from 'model' directory." << endl;
			Info << " WARNING! Make sure it's not a single volume structure." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setPair(id0, id1)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

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
				auto address = file::GetSystemFile("tnbCadToolVolumeSetPairs");
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
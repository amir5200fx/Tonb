#include <Mesh3d_ReferenceValues.hxx>
#include <GeoSizeFun3d_Uniform.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string saveExt = Geo3d_SizeFunction::extension;
	static const std::string loadExt = Mesh3d_ReferenceValues::extension;

	static unsigned short verbose = 0;
	static bool exeTag = false;
	static bool loadTag = false;

	static std::shared_ptr<Mesh3d_ReferenceValues> myRef;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static const auto current_directory = "reference";

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadRefFile()
	{
		myRef = 
			file::LoadSingleFile<std::shared_ptr<Mesh3d_ReferenceValues>>
			(current_directory, Mesh3d_ReferenceValues::extension, verbose);
		loadTag = true;
		if (NOT myRef)
		{
			FatalErrorIn(FunctionSIG)
				<< "no ref file has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadRefFile(const std::string& name)
	{
		file::CheckExtension(name);
		myRef = file::LoadFile<std::shared_ptr<Mesh3d_ReferenceValues>>
			(name + Mesh3d_ReferenceValues::extension, verbose);
		if (NOT myRef)
		{
			FatalErrorIn(FunctionSIG)
				<< "no ref file has been loaded." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		if (file::IsDirectory(current_directory))
		{
			loadRefFile();
		}
		else
		{
			auto name = 
				file::GetSingleFile
				(
					boost::filesystem::current_path(),
					Mesh3d_ReferenceValues::extension
				).string();
			loadRefFile(name);
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
		file::SaveTo(mySizeFun, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(mySizeFun->Name());
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		mySizeFun = std::make_shared<GeoSizeFun3d_Uniform>
			(0, name, myRef->BaseSize(), *myRef->Region());

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("uniSizeMap");
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
		// io functions [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadRefFile(name); }), "load_file");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "save_to");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "save_to");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "set_verbose");

		// operators [12/9/2021 Amir]
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
			Info << " This application is aimed to create a uniform size map." << endl << endl;

			Info << " You can load the reference from 'reference' directory." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int); Levels: 0, 1, 2" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMeshSizeMapUniform"));

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
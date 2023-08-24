#include <MeshPost_IdeasUNV.hxx>
#include <Geo3d_FVMesh.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Geo3d_FVMesh> myFvMesh;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;
	TNB_DEFINE_FILENAME_OBJ;
	static const std::string sub_directory = "mesh";

	TNB_SET_VERBOSE_FUN;

	void loadMesh(const std::string& name)
	{
		file::CheckExtension(name);
		myFvMesh =
			file::LoadFile<std::shared_ptr<Geo3d_FVMesh>>(name + Geo3d_FVMesh::extension, verbose);
		TNB_CHECK_LOADED_FILE(myFvMesh);
		loadTag = true;
		myFileName = name;
	}

	void loadMesh()
	{
		myFvMesh =
			file::LoadSingleFile<std::shared_ptr<Geo3d_FVMesh>>
			(sub_directory, Geo3d_FVMesh::extension, verbose, myFileName);
		loadTag = true;
		TNB_CHECK_LOADED_FILE(myFvMesh);
	}

	void loadFile()
	{
		if (file::IsDirectory(sub_directory))
		{
			loadMesh();
		}
		else
		{
			auto name =
				file::GetSingleFile(file::GetCurrentPath(), Geo3d_FVMesh::extension).string();
			loadMesh(name);
		}
	}

	void execute(const std::string& myFileName)
	{
		TNB_CHECK_LOAD_TAG;
		auto convertor = std::make_shared<MeshPost_IdeasUNV>();
		convertor->SetMesh(myFvMesh);
		convertor->Perform(myFileName);
		TNB_PERFORMED_TAG;
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
		// io functions [1/23/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadMesh(name); }), "loadFile");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [1/23/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short c)->void {setVerbose(c); }), "setVerbose");

		// operators [1/23/2023 Payvand]
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
			Info << endl;
			Info << " This application is aimed to save a FvMesh into a UNV file format." << endl << endl;

			Info << " - subdirectory: {" << sub_directory << "}" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Operators: " << endl << endl

				<< " - execute(fileName)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
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
				fileName myFileName(file::GetSystemFile("tnbFvMeshToUNV"));

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
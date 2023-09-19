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

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name + ".plt");
		OFstream myFile(fn);

		myFvMesh->ExportToPlt(myFile);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been loaded!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadMesh(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings

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

int main(int argc, char* argv[])
{
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to convert a mesh file to the *.plt file format." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl

				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbFvMeshToPlt"));
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
#include <MeshPost_Extrude.hxx>
#include <MeshPost2d_OFTopology.hxx>
#include <MeshIO2d_FEA.hxx>
#include <Geo3d_FVMesh.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<MeshIO2d_FEA> myMeshIO;
	static std::shared_ptr<Geo3d_FVMesh> myFvMesh;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;
	TNB_DEFINE_FILENAME_OBJ;
	static const std::string sub_directory = "mesh";

	TNB_SET_VERBOSE_FUN;

	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myMeshIO, sub_directory, myFvMesh);

	void execute(const std::string& theName)
	{
		TNB_CHECK_LOAD_TAG;
		auto topology = std::make_shared<MeshPost2d_OFTopology>();
		topology->SetMeshIO(myMeshIO);
		topology->Perform();

		auto convertor = std::make_shared<MeshPost_Extrude>();
		convertor->SetMesh2d(topology);
		convertor->SetTitle(theName);
		convertor->Perform();

		myFvMesh = convertor->RetrieveIO();
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

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
			Info << " This application is aimed to extrude a two-dimensional mesh." << endl << endl;

			Info << " - subdirectory: {" << sub_directory << "}" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Operators: " << endl << endl

				<< " - execute(name)" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMesh2dExtrude"));

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
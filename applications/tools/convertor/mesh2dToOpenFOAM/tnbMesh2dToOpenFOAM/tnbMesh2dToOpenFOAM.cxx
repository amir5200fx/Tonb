#include <MeshPost2d_ConvertToOpenFOAM.hxx>
#include <MeshPost2d_OFTopology.hxx>
#include <MeshIO2d_FEA.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<MeshIO2d_FEA> myMeshIO;

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
		myMeshIO = 
			file::LoadFile<std::shared_ptr<MeshIO2d_FEA>>(name + MeshIO2d_FEA::extension, verbose);
		TNB_CHECK_LOADED_FILE(myMeshIO);
		loadTag = true;
		myFileName = name;
	}

	void loadMesh()
	{
		myMeshIO = 
			file::LoadSingleFile<std::shared_ptr<MeshIO2d_FEA>>
			(sub_directory, MeshIO2d_FEA::extension, verbose, myFileName);
		loadTag = true;
		TNB_CHECK_LOADED_FILE(myMeshIO);
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
				file::GetSingleFile(file::GetCurrentPath(), MeshIO2d_FEA::extension).string();
			loadMesh(name);
		}
	}

	void execute()
	{
		TNB_CHECK_LOAD_TAG;
		auto topology = std::make_shared<MeshPost2d_OFTopology>();
		topology->SetMeshIO(myMeshIO);
		topology->Perform();
		/*for (const auto& x : topology->Interiors())
		{
			std::cout << "id: " << x.Index() << ", owner: " << x.Owner() << ", neighbor: " << x.Neighbor() << std::endl;
		}*/
		/*PAUSE;
		for (const auto& x : topology->Boundaries())
		{
			for (const auto& p : x.second)
			{
				std::cout << "physic: " << x.first << ", id: " << p.Index() << ", owner: " << p.Owner() << ", neighbor: " << p.Neighbor() << std::endl;
			}
			
		}*/
		auto convertor = std::make_shared<MeshPost2d_ConvertToOpenFOAM>();
		convertor->SetMesh(topology);
		convertor->Perform();
		convertor->Export();
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
			Info << " This application is aimed to convert a two-dimensional mesh to OpenFOAM mesh." << endl << endl;

			Info << " - subdirectory: {" << sub_directory << "}" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Operators: " << endl << endl
				<< " - execute()" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMesh2dToOpenFOAM"));

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
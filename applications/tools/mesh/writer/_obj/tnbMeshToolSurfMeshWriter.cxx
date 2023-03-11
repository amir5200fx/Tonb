#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx> 
#include <Entity3d_Box.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <Global_File.hxx>
#include <OFstream.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Triangulation> myMesh;
	static const std::string extension = Entity3d_Triangulation::extension;

	std::string myFileName;

	static unsigned short verbose(0);
	static bool loadTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadMesh3d()
	{
		checkFolder("mesh");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\mesh)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
				myFileName = name;
				myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
				if (NOT myMesh)
				{
					FatalErrorIn(FunctionSIG)
						<< " the mesh file is null!" << endl
						<< abort(FatalError);
				}
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
			myFileName = name;
			myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
			if (NOT myMesh)
			{
				FatalErrorIn(FunctionSIG)
					<< " the mesh file is null!" << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadMeshFile(const std::string& name)
	{
		file::CheckExtension(name);
		myFileName = name;
		myMesh = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
		if (NOT myMesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the mesh is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("mesh"))
		{
			loadMesh3d();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Triangulation::extension).string();
			myFileName = name;
			loadMeshFile(name);
		}

		loadTag = true;
	}

	void loadFile(const std::string& name)
	{
		loadMeshFile(name);

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

		std::ofstream myFile(name + ".obj", std::ios::out);
		if (NOT myFile.is_open())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file:" << endl
				<< " - file name = " << name << endl
				<< abort(FatalError);
		}
		Geo_Tools::ExportAsOBJ_cgal(*myMesh, myFile);
		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << name + ".obj" << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/21/2021 Amir]
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
			Info << " This application is aimed to save a mesh as *.obj file format." << endl
				<< " - subdirectories: mesh" << endl;
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

			setFuns(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshToolSurfMeshWriter"));
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
#include <GMesh_Lib.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity_Connectivity.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;

	static std::string myShapeName;

	static std::shared_ptr<Cad_Shape> myShape;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeMap;

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

	void loadModel()
	{
		checkFolder("model");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\model)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			myShapeName = name;
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				{
					auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();

					myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
					if (NOT myShape)
					{
						FatalErrorIn(FunctionSIG)
							<< " the model is null." << endl
							<< abort(FatalError);
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl;
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();
			myShapeName = name;
			myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
			if (NOT myShape)
			{
				FatalErrorIn(FunctionSIG)
					<< " the model is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadSizeMap()
	{
		checkFolder("sizeMap");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\sizeMap)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				{
					auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();

					mySizeMap = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
					if (NOT mySizeMap)
					{
						FatalErrorIn(FunctionSIG)
							<< " the sizeMap is null." << endl
							<< abort(FatalError);
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl;
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();

			mySizeMap = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
			if (NOT mySizeMap)
			{
				FatalErrorIn(FunctionSIG)
					<< " the sizeMap is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);
		myShapeName = name;
		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape is null." << endl
				<< abort(FatalError);
		}
	}

	void loadSizeMap(const std::string& name)
	{
		file::CheckExtension(name);
		mySizeMap = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
		if (NOT mySizeMap)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("model"))
		{
			loadModel();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Shape::extension).string();
			loadModel(name);
		}

		if (boost::filesystem::is_directory("sizeMap"))
		{
			loadSizeMap();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();
			loadSizeMap(name);
		}

		loadTag = true;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			Info << endl
				<< " no file has been loaded." << endl
				<< abort(FatalError);
		}

		GMesh_Lib::Initialize();

		GMesh_Lib::AddModel("myModel");

		Cad_Tools::ExportToIGES("mm", myShape->Shape(), myShapeName + ".iges");

		std::vector<std::pair<int, int>> v;
		GMesh_Lib::ImportIGES(myShapeName + ".iges", v);

		
		//GMesh_Lib::ImportShape(myShape->Shape(), v);

		GMesh_Lib::SetSizeMap(*mySizeMap);

		GMesh_Lib::SynchronizeShape();

		GMesh_Lib::Generate(3);

		GMesh_Lib::WriteMesh("myModel.msh");

		GMesh_Lib::Finalize();

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
		exeTag = true;
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

		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// Operators [2/11/2023 Payvand]
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
			Info << " This application is aimed to discrete a volume by Delaunay method." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshVolumeDelaunay"));

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
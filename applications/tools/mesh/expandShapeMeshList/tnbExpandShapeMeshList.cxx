#include <Entity3d_Triangulation.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;

	static const std::string extension = Entity3d_Triangulation::extension + "list";

	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myTris;
	static std::string myFileName;

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

	void loadMesh()
	{
		checkFolder("list");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\list)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				while (std::getline(myFile, address))
				{
					// change the current path [2/6/2023 Payvand]
					boost::filesystem::current_path(address);

					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
						myFileName = name;
						myTris = file::LoadFile<std::vector<std::shared_ptr<Entity3d_Triangulation>>>(name + extension, verbose);
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
			myFileName = name;
			myTris = file::LoadFile<std::vector<std::shared_ptr<Entity3d_Triangulation>>>(name + extension, verbose);
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myTris = file::LoadFile<std::vector<std::shared_ptr<Entity3d_Triangulation>>>(name + extension, verbose);
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("list"))
		{
			loadMesh();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
			myFileName = name;
			loadFile(name);
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		auto current = fs::current_path().string();
		std::string address = current + "\\results";
		fs::path dir(address);
		if (NOT fs::is_directory(dir))
		{
			fs::create_directory(dir);
		}
		else
		{
			file::RemoveDirectory(dir);
			fs::create_directory(dir);
		}

		fs::current_path(dir);

		size_t i = 0;
		for (const auto& x : myTris)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + Entity3d_Triangulation::extension, verbose);

			fs::current_path(dir);

			++i;
		}

		fs::current_path(current);
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
			Info << " This application is aimed to expand a list of surface meshes." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl
				<< " - setTolerance(x)" << endl

				<< " # Operators:" << endl 
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
				fileName myFileName(file::GetSystemFile("tnbExpandShapeMeshList"));

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
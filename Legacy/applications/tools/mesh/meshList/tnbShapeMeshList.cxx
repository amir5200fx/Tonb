#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Serialization.hxx>
#include <Global_File.hxx>

#include <vector>

#include <boost/filesystem.hpp>

namespace tnbLib
{
	static const std::string loadExt = Entity3d_Triangulation::extension;
	static const std::string saveExt = Entity3d_Triangulation::extension + "list";

	typedef std::shared_ptr<Entity3d_Triangulation> tri_t;

	static std::vector<tri_t> myChains;

	static bool loadTag = false;
	static unsigned short verbose = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadMeshes(const std::string& name)
	{
		file::CheckExtension(name);

		if (verbose)
		{
			Info << "loading the meshes..." << endl;
			Info << endl;
		}

		size_t i = 0;
		while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name + loadExt;
			std::fstream file;
			file.open(address, std::ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);

			tri_t mesh;
			ia >> mesh;

			if (verbose)
			{
				Info << " - mesh, " << i << ", is loaded from: " << address << ", successfully!" << endl;
			}

			myChains.push_back(std::move(mesh));
			i++;
		}
		if (verbose)
		{
			Info << endl
				<< " All files are loaded, successfully!" << endl;
		}

		loadTag = true;
	}

	void loadMeshes()
	{
		if (verbose)
		{
			Info << "loading the meshes..." << endl;
			Info << endl;
		}

		size_t i = 0;
		while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
		{
			auto name = file::GetSingleFile(boost::filesystem::path(std::to_string(i)), loadExt).string();
			std::string address = ".\\" + std::to_string(i) + "\\" + name + loadExt;
			std::fstream file;
			file.open(address, std::ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);

			tri_t mesh;
			ia >> mesh;

			if (verbose)
			{
				Info << " - mesh, " << i << ", is loaded from: " << address << ", successfully!" << endl;
			}

			myChains.push_back(std::move(mesh));
			i++;
		}
		if (verbose)
		{
			Info << endl
				<< " All files are loaded, successfully!" << endl;
		}

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

		fileName fn(name + saveExt);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myChains;
		if (verbose)
		{
			Info << endl;
			Info << " meshes are saved in: " << fn << ", successfully!" << endl;
		}
	}

	void saveTo()
	{
		saveTo("mesh");
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadMeshes(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadMeshes(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](unsigned short c)->void {verbose = c; }), "setVerbose");
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
			Info << endl;
			Info << "This application is aimed to a mesh list." << endl;
			Info << endl;
			Info << " Function list:" << endl << endl

				<< " - setVerbose(unsigned short)" << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(string)" << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				//std::string address = ".\\system\\tnbShapeMeshList";
				fileName myFileName(file::GetSystemFile("tnbShapeMeshList"));

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
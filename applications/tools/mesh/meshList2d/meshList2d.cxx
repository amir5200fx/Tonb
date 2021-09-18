#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Serialization.hxx>

#include <vector>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Entity2d_Triangulation> tri_t;

	static std::vector<tri_t> myChains;

	static bool loadTag = false;
	static unsigned short verbose = 0;

	void loadChains(const std::string& name)
	{
		if (verbose)
		{
			Info << "loading the meshes..." << endl;
			Info << endl;
		}

		size_t i = 0;
		while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

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
			if (myChains.size() > 1)
			{
				Info << endl;
				Info << " " << myChains.size() << " nb. of meshes have been loaded." << endl;
			}
			else
			{
				Info << endl;
				Info << " " << myChains.size() << " mesh has been loaded." << endl;
			}
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myChains;
		if (verbose)
		{
			Info << endl;
			Info << " meshes are saved in: " << fn << ", successfully!" << endl;
		}
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadChains(name); }), "loadMeshes");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\TnbMeshList2d";
			fileName myFileName(address);

			try
			{
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
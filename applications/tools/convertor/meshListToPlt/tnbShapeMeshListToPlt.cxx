#include <Entity3d_Triangulation.hxx> 
#include <Entity3d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OFstream.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	static const std::string loadExt = Entity3d_Triangulation::extension + "list";
	static const std::string saveExt = ".plt";

	typedef std::shared_ptr<Entity3d_Triangulation> mesh_t;

	static unsigned short verbose(0);

	static bool loadTag = false;
	static std::string myFileName;

	static std::vector<mesh_t> myMeshes;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		myMeshes = file::LoadFile<std::vector<mesh_t>>(name + loadExt, verbose);

		loadTag = true;
	}

	void loadModel()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadModel(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been loaded!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		fileName fn(name + saveExt);
		OFstream myFile(fn);

		for (const auto& x : myMeshes)
		{
			if (x)
			{
				x->ExportToPlt(myFile);
			}
		}

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
		}
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadMesh");
		mod->add(chaiscript::fun([]()-> void {loadModel(); }), "loadMesh");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");


		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
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
			Info << "This application is aimed to convert a mesh list to *.plt file format." << endl;
			Info << endl;
			Info << " Function list:" << endl <<endl
				<< " - setVerbose(unsigned short)" << endl <<endl
				<< " - loadMesh(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				//std::string address = ".\\system\\tnbShapeMeshListToPlt";
				fileName theFileName(file::GetSystemFile("tnbShapeMeshListToPlt"));

				chai.eval_file(theFileName);
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
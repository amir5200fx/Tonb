#include <Entity3d_Triangulation.hxx> 
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OFstream.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<Entity3d_Triangulation> mesh_t;

	static unsigned short verbose(0);

	static bool loadTag = false;

	static std::vector<mesh_t> myMeshes;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the list from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> myMeshes;

		if (verbose)
		{
			Info << endl;
			Info << " the mesh list is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void exportTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		OFstream myFile(fn);

		for (const auto& x : myMeshes)
		{
			if (x)
			{
				x->ExportToPlt(myFile);
			}
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

	void setFunctions(const module_t& mod)
	{
		//- io functions

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadMesh");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportTo(name); }), "saveTo");
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
				<< " - loadMesh(string)" << endl
				<< " - saveTo(string)" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbShapeMeshListToPlt";
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
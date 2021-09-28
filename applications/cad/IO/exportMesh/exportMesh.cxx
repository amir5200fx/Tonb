#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Cad_Shape> shape_t;

	static shape_t myShape;
	static unsigned short verbose(0);
	static bool loadtag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> myShape;
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded shape is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the shape is loaded, from: " << name << ", successfully!" << endl;
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

		loadtag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadtag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		auto mesh = Cad_Tools::RetrieveTriangulation(myShape->Shape());
		if (mesh.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been found for the shape!" << endl
				<< abort(FatalError);
		}

		auto tris = std::make_shared<Entity3d_Triangulation>();
		for (const auto& x : mesh)
		{
			if (x)
			{
				auto tri = Cad_Tools::Triangulation(*x);
				if (tri)
				{
					tris->Add(*tri);
				}
			}
		}

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << tris;

		if (verbose)
		{
			Info << endl;
			Info << " the triangulation is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
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

		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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
			Info << "This application is aimed to retrieve the mesh of the surfaces." << endl;
			Info << endl;
			Info << " Function list:" << endl
				<< " - setVerbose(unsigned short)" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\exportShapeMesh";
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

}
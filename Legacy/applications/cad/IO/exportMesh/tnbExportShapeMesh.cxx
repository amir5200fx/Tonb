#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Cad_Shape> shape_t;

	static const std::string loadExt = Cad_Shape::extension;
	static const std::string saveExt = Entity3d_Triangulation::extension + "list";

	static shape_t myShape;
	static unsigned short verbose(0);
	static bool loadTag = false;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + loadExt, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

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
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		auto mesh = Cad_Tools::RetrieveTriangulation(myShape->Shape());
		if (mesh.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no mesh has been found for the shape!" << endl
				<< abort(FatalError);
		}

		std::vector<std::shared_ptr<Entity3d_Triangulation>> tris;
		for (const auto& x : mesh)
		{
			if (x)
			{
				auto tri = Cad_Tools::Triangulation(*x);
				if (tri)
				{
					tris.push_back(std::move(tri));
				}
			}
		}

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << tris;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the triangulation is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([]()-> void {loadModel(); }), "loadModel");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings

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
			Info << "This application is aimed to retrieve the mesh of the surfaces." << endl;
			Info << endl;
			Info << " Function list:" << endl
				<< " - setVerbose(unsigned short)" << endl << endl

				<< " - loadModel(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl;
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
				//std::string address = ".\\system\\tnbExportShapeMesh";
				fileName myFileName(file::GetSystemFile("tnbExportShapeMesh"));

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
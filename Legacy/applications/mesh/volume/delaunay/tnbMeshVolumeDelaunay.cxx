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

	static std::string my_file_name;

	static std::shared_ptr<Cad_Shape> my_shape;
	static std::shared_ptr<Geo3d_SizeFunction> my_size_map;

	void set_verbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void load_model(const std::string& name)
	{
		file::CheckExtension(name);
		my_file_name = name;
		my_shape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + Cad_Shape::extension, verbose);
		if (NOT my_shape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape file contains null object." << endl
				<< abort(FatalError);
		}
	}

	void load_size_map(const std::string& name)
	{
		file::CheckExtension(name);
		my_size_map = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
		if (NOT my_size_map)
		{
			FatalErrorIn(FunctionSIG)
				<< " the size map contains null object." << endl
				<< abort(FatalError);
		}
	}

	void execute()
	{
		if (NOT my_shape)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - No geometric model has been loaded." << endl
				<< abort(FatalError);
		}
		if (NOT my_size_map)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No size map function has been loaded." << endl
				<< abort(FatalError);
		}
		GMesh_Lib::Initialize();

		GMesh_Lib::AddModel("myModel");

		Cad_Tools::ExportToIGES("mm", my_shape->Shape(), my_file_name + ".iges");

		std::vector<std::pair<int, int>> v;
		GMesh_Lib::ImportIGES(my_file_name + ".iges", v);

		
		//GMesh_Lib::ImportShape(myShape->Shape(), v);

		GMesh_Lib::SetSizeMap(*my_size_map);

		GMesh_Lib::SynchronizeShape();

		GMesh_Lib::Generate(3);

		GMesh_Lib::WriteMesh("myModel.msh");

		GMesh_Lib::Finalize();

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

		mod->add(chaiscript::fun([](const std::string& name)->void {load_model(name); }), "load_model");
		mod->add(chaiscript::fun([](const std::string& name)->void {load_size_map(name); }), "load_size_map");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "set_verbose");

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

				<< " - load_model(name)" << endl
				<< " - load_size_map(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int); Levels: 0, 1" << endl << endl

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
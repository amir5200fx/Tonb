#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::shared_ptr<Entity3d_Triangulation> my_tris;
	static const std::string extension = Entity3d_Triangulation::extension;
	static unsigned short verbose = 0;
	static std::string my_file_name;

	void set_verbose(unsigned short i)
	{
		Info << "\n"
			<< " - VERBOSE has been set to: " << i << "\n";
		verbose = i;
	}

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_tris = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + extension, verbose);
		if (NOT my_tris)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the loaded file contains no data!" << endl
				<< abort(FatalError);
		}
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		my_file_name = name;
		load_file(my_file_name);
	}

	void save_to(const std::string& name)
	{
		if (NOT my_tris)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "No mesh file has been loaded." << endl
				<< abort(FatalError);
		}
		OFstream my_file(name + ".vtk");
		my_tris->ExportToVtk(my_file);
		if (verbose)
		{
			Info << "\n"
				<< " - The file is successfully saved as " << name << "\n";
		}
	}

	void save_to()
	{
		save_to(my_file_name);
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;
	void set_functions(const module_t mod)
	{
		// io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {load_file(name); }), "load_file");
		mod->add(chaiscript::fun([]()->void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)->void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()->void {save_to(); }), "save_to");

		// Settings
		mod->add(chaiscript::fun([](unsigned short i)->void {set_verbose(i); }), "set_verbose");
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
			Info << "This application is aimed to convert the mesh to *.vtk file format." << endl;
			Info << endl;
			Info << " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned short)" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			set_functions(mod);

			chai.add(mod);

			try
			{
				//std::string address = ".\\system\\tnbShapeMeshToPlt";
				fileName myFileName(file::GetSystemFile("tnbShapeMeshToVtk"));

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
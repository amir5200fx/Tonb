#include <GeoIO_Loader_STL.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static bool loadTag = false;

	static std::shared_ptr<Entity3d_Triangulation> my_mesh;
	static const std::string extension = ".stl";

	static std::string my_file_name;

	TNB_SET_VERBOSE_FUN;

	void load_file_binary(const std::string& file_name)
	{
		file::CheckExtension(file_name);
		my_file_name = file_name;

		auto loader = std::make_shared<ioLib::Loader_STL>();
		loader->Perform(my_file_name + extension);
		my_mesh = loader->Mesh();
		loadTag = true;
	}

	void load_file_ascii(const std::string& file_name)
	{
		file::CheckExtension(file_name);
		my_file_name = file_name;

		auto loader = std::make_shared<ioLib::Loader_STL>();
		loader->Perform(file_name + extension);
		my_mesh = loader->Mesh();
		loadTag = true;
	}

	void save_to(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No file has been loaded!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_mesh, name + Entity3d_Triangulation::extension, verbose);
	}

	void save_to()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No file has been loaded!" << endl
				<< abort(FatalError);
		}
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file_binary(name); }), "load_binary_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file_ascii(name); }), "load_ascii_file");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "set_verbose");

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
			Info << " This application is aimed to load an *.stl file format." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_binary_file(name)" << endl
				<< " - load_ascii_file(name)" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int); Levels: 0, 1" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMeshToolLoaderSTL"));

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
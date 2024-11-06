#include <Aft3d_SizeFun_Uniform.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::shared_ptr<legLib::Aft3d_SizeFun> my_size_fun;
	static std::shared_ptr<Entity3d_Triangulation> my_model;
	static unsigned int verbose = 0;
	static double my_value = 0;

	void set_verbose(unsigned int i)
	{
		Info << "\n"
			<< " - VERBOSITY has been set to: " << i << "\n";
		verbose = i;
	}

	void set_value(double x)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - VALUE has been set to: " << x << "\n";
		}
		my_value = x;
	}

	void load_model(const std::string& name)
	{
		file::CheckExtension(name);
		my_model = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(name + Entity3d_Triangulation::extension, verbose);
		if (NOT my_model)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The model file contains no data." << endl
				<< abort(FatalError);
		}
	}

	void save_to(const std::string& name)
	{
		if (NOT my_size_fun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The application has been performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_size_fun, name + legLib::Aft3d_SizeFun_Uniform::extension, verbose);
	}

	void execute()
	{
		if (NOT my_model)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No model has been loaded." << endl
				<< abort(FatalError);
		}
		if (NOT my_value)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No value has been assigned." << endl
				<< abort(FatalError);
		}
		auto b = Geo_BoxTools::GetBox(my_model->Points(), 0);
		b.Expand(b.Diameter() * 1.e-3);
		my_size_fun = std::make_shared<legLib::Aft3d_SizeFun_Uniform>(std::make_shared<Entity3d_Box>(b), my_value);
		if (verbose)
		{
			Info << "\n"
				<< " - The application has been successfully performed." << "\n";
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

	void set_functions(const module_t& mod)
	{
		// io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {load_model(name); }), "load_model");
		mod->add(chaiscript::fun([](const std::string& name)->void {save_to(name); }), "save_to");

		// settings
		mod->add(chaiscript::fun([](unsigned int i)->void {set_verbose(i); }), "set_verbose");
		mod->add(chaiscript::fun([](double x)->void {set_value(x); }), "set_value");

		// operators
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a size function." << endl
				<< endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_model(file_name);          - surface mesh" << endl
				<< " - save_to(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_value(x)" << endl
				<< " - set_verbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			set_functions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshSizeMapUniformLegacy"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}
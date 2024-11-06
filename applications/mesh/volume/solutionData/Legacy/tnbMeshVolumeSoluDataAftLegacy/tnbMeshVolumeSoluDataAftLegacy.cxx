#include <Aft3d_SolutionData.hxx>
#include <Aft3d_SizeFun.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned int verbose = 0;

	static std::shared_ptr<Entity3d_Triangulation> my_surface;
	static std::shared_ptr<legLib::Aft3d_SizeFun> my_size_fun;
	static std::shared_ptr<legLib::Aft3d_SolutionData> my_solu_data;

	void set_verbose(unsigned int i)
	{
		Info << "\n"
			<< " - VERBOSE has been set to: " << i << "\n";
		verbose = i;
	}

	void load_surface(const std::string& name)
	{
		file::CheckExtension(name);
		const auto surface = file::LoadFile<std::shared_ptr<Entity3d_Triangulation>>(
			name + Entity3d_Triangulation::extension, verbose);
		if (NOT surface)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The surface mesh file contains no mesh!" << endl
				<< abort(FatalError);
		}
		my_surface = surface;
	}

	void load_size_fun(const std::string& name)
	{
		file::CheckExtension(name);
		const auto size_fun = file::LoadFile<std::shared_ptr<legLib::Aft3d_SizeFun>>(
			name + legLib::Aft3d_SizeFun::extension, verbose);
		if (NOT size_fun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The size function file contains no object!" << endl
				<< abort(FatalError);
		}
		my_size_fun = size_fun;
	}

	void save_to(const std::string& name)
	{
		if (NOT my_solu_data)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The application haven't been performed!" << endl
				<< abort(FatalError);
		}
		file::SaveTo(my_solu_data, name + legLib::Aft3d_SolutionData::extension, verbose);
	}

	void execute()
	{
		if (NOT my_surface)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No surface mesh has been loaded." << endl
				<< abort(FatalError);
		}
		if (NOT my_size_fun)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No size function has been loaded." << endl
				<< abort(FatalError);
		}
		my_solu_data = std::make_shared<legLib::Aft3d_SolutionData>();
		my_solu_data->SetSurface(my_surface);
		my_solu_data->SetSizeFun(my_size_fun);
		if (verbose)
		{
			Info << "\n"
				<< " - The application has been successfully performed.\n";
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
		mod->add(chaiscript::fun([](const std::string& name)->void {load_surface(name); }), "load_surface");
		mod->add(chaiscript::fun([](const std::string& name)->void {load_size_fun(name); }), "load_size_function");
		mod->add(chaiscript::fun([](const std::string& name)->void {save_to(name); }), "save_to");

		// settings
		mod->add(chaiscript::fun([](unsigned int i)->void {set_verbose(i); }), "set_verbose");

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
			Info << " This application is aimed to create a solution data of the volume mesh." << endl
				<< endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_surface(file_name);        - surface mesh" << endl
				<< " - load_size_function(file_name);  - size function" << endl
				<< " - save_to(name)" << endl << endl

				<< " # Settings: " << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbMeshVolumeSoluDataAftLegacy"));

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
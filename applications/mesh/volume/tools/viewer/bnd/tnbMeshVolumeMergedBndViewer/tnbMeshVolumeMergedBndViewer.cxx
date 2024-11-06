#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static std::string my_file_name;

	static std::shared_ptr<Aft3d_SolutionData_SurfVol> my_solu_data;
	static const auto load_extension = Aft3d_SolutionData_SurfVol::extension;
	static const auto save_extension = Entity3d_Triangulation::extension;

	static std::shared_ptr<Entity3d_Triangulation> my_mesh;

	void set_verbose(unsigned short i)
	{
		Info << "\n"
			<< " - VERBOSE has been set to: " << i << "\n";
		verbose = i;
	}

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_solu_data = file::LoadFile<std::shared_ptr<Aft3d_SolutionData_SurfVol>>(name + load_extension, verbose);
		if (NOT my_solu_data)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The loading file contains no data!" << endl
				<< abort(FatalError);
		}
		my_file_name = name;
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), load_extension).string();
		load_file(name);
	}

	void save_to(const std::string& name)
	{
		if (NOT my_mesh)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The application hasn't performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_mesh, name + save_extension, verbose);
	}

	void save_to()
	{
		save_to(my_file_name);
	}

	void execute()
	{
		if (NOT my_solu_data)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " No solution data has been loaded." << endl
				<< abort(FatalError);
		}
		my_mesh = my_solu_data->Merged();
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

	void setFuns(const module_t& mod)
	{
		// io functions 
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file(name); }), "load_file");

		// settings 
		mod->add(chaiscript::fun([](unsigned short i)-> void {set_verbose(i); }), "set_verbose");

		// operators 
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
			Info << " This application is aimed to retrieve the triangulations from a solution data." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshVolumeMergedBndViewer"));

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
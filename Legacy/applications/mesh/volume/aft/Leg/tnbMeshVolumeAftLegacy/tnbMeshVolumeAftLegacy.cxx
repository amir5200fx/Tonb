#include <Aft3d_Volume.hxx>
#include <Aft3d_SolutionData.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static unsigned int verbose = 0;
	static bool exe_tag = false;
	static std::string my_file_name;
	static std::shared_ptr<legLib::Aft3d_SolutionData> my_solu_data;
	static std::string extension = legLib::Aft3d_SolutionData::extension;

	void set_verbose(unsigned int i)
	{
		Info << "\n"
			<< " - The verbosity level has been set to: " << i << "\n";
		verbose = i;
	}

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_solu_data = file::LoadFile<std::shared_ptr<legLib::Aft3d_SolutionData>>(name + extension, verbose);
		my_file_name = name;
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		load_file(name);
	}

	void save_to(const std::string& name)
	{
		if (!exe_tag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " The application has not been performed." << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_solu_data, name + extension, verbose);
	}

	void save_to()
	{
		save_to(my_file_name);
	}

	void execute()
	{
		if (!my_solu_data)
		{
			FatalErrorIn(FunctionSIG) << "\n"
				<< "no solution data file has been loaded." << "\n"
				<< abort(FatalError);
		}
		legLib::Aft3d_Volume::verbose = verbose - 1;
		const auto bnd_mesh = my_solu_data->Surface();
		auto alg = std::make_shared<legLib::Aft3d_Volume>();
		alg->Import(*bnd_mesh);
		
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
		mod->add(chaiscript::fun([](const std::string& name)->void {load_file(name); }), "load_file");
		mod->add(chaiscript::fun([]()->void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name) ->void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()->void {save_to(); }), "save_to");

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
			Info << " This application is aimed to discrete a volume." << endl
				<< endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(file_name);" << endl
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
				fileName theFileName(file::GetSystemFile("tnbMeshVolumeAftLegacy"));

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

#include <Cad_SingleVolume.hxx>
#include <Cad_Solid.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;

	TNB_SET_VERBOSE_FUN;

	static std::shared_ptr<Cad_Solid> my_solid;
	static std::shared_ptr<Cad_Volume> my_volume;

	void load_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_solid = file::LoadFile<std::shared_ptr<Cad_Solid>>(name + Cad_Solid::extension, verbose);
		if (NOT my_solid)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the file contains a null solid." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void load_file()
	{
		const auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_Solid::extension).string();
		myFileName = name;
		load_file(name);
	}

	void save_to(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_volume, name + Cad_Volume::extension, verbose);
	}

	void save_to()
	{
		save_to(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		my_volume = std::make_shared<Cad_SingleVolume>(my_solid->Index(), my_solid->Name(), my_solid);
		exeTag = true;
		if (verbose)
		{
			Info << " - The volume has been successfully created." << endl;
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
		mod->add(chaiscript::fun([]()->void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_file(name); }), "load_file");

		// settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "set_verbose");

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
	FatalError.throwExceptions();
	FatalConvError.throwExceptions();

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
			Info << " This application is aimed to make a single volume from a solid." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

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

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadSingleVolume"));

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
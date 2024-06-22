#include <Mesh3d_ReferenceValues.hxx>
#include <GeoSizeFun3d_Uniform.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string save_ext = Geo3d_SizeFunction::extension;

	static unsigned short verbose = 0;
	static bool exeTag = false;
	static bool load_tag = false;

	static std::shared_ptr<Mesh3d_ReferenceValues> my_ref;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static const auto current_directory = "reference";

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void set_verbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void load_ref_file()
	{
		my_ref = 
			file::LoadSingleFile<std::shared_ptr<Mesh3d_ReferenceValues>>
			(current_directory, Mesh3d_ReferenceValues::extension, verbose);
		load_tag = true;
		if (NOT my_ref)
		{
			FatalErrorIn(FunctionSIG)
				<< "no ref file has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void load_ref_file(const std::string& name)
	{
		file::CheckExtension(name);
		my_ref = file::LoadFile<std::shared_ptr<Mesh3d_ReferenceValues>>
			(name + Mesh3d_ReferenceValues::extension, verbose);
		if (NOT my_ref)
		{
			FatalErrorIn(FunctionSIG)
				<< "no ref file has been loaded." << endl
				<< abort(FatalError);
		}
		load_tag = true;
	}

	void load_file()
	{
		if (file::IsDirectory(current_directory))
		{
			load_ref_file();
		}
		else
		{
			auto name = 
				file::GetSingleFile
				(
					boost::filesystem::current_path(),
					Mesh3d_ReferenceValues::extension
				).string();
			load_ref_file(name);
		}
	}

	void save_to(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(mySizeFun, name + save_ext, verbose);
	}

	void save_to()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		save_to(mySizeFun->Name());
	}

	void execute(const std::string& name)
	{
		if (NOT load_tag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		mySizeFun = std::make_shared<GeoSizeFun3d_Uniform>
			(0, name, my_ref->BaseSize(), *my_ref->Region());

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("uniSizeMap");
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
		// io functions [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {load_file(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {load_ref_file(name); }), "load_file");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");
		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {set_verbose(i); }), "set_verbose");

		// operators [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
			Info << " This application is aimed to create a uniform size map." << endl << endl;
			Info << " - Requirements: A *." << Mesh3d_ReferenceValues::extension << " file must be loaded." << endl;

			Info << " You can load the reference from " << current_directory << " directory." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - load_file(name [optional])" << endl
				<< " - save_to(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - set_verbose(unsigned int);               - Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshSizeMapUniform"));

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
#include <Cad2d_Boolean.hxx>
#include <Cad2d_Plane.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::vector<std::shared_ptr<Cad2d_Plane>> myPlanes;

	static std::shared_ptr<Cad2d_Plane> myPlane0;
	static std::shared_ptr<Cad2d_Plane> myPlane1;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;

	static double myTol = 1.0E-6;
	static unsigned short myTarget = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTol(double t)
	{
		myTol = t;
		if (verbose)
		{
			Info << endl
				<< " - the tol. is set to: " << myTol << endl;
		}
	}

	void setTarget(unsigned short i)
	{
		if (i == 0)
		{
			myTarget = i;
			Info << endl
				<< " - the target is set to: plane 0" << endl;
		}
		else if(i == 1)
		{
			myTarget = i;
			Info << endl
				<< " - the target is set to: plane 1" << endl;
		}
		else
		{
			// do nothing [6/26/2023 Payvand]
		}
	}

	void loadPlane0()
	{
		static const auto current_directory = "0";
		file::CheckDirectory(current_directory);

		//file::SetCurrentPath(global_path.string() + "/" + current_directory);
		myPlane0 = file::LoadSingleFile<std::shared_ptr<Cad2d_Plane>>(current_directory, verbose);
		TNB_CHECK_LOADED_FILE(myPlane0);
		file::SetCurrentPath(global_path.string());
	}

	void loadPlane1()
	{
		static const auto current_directory = "1";
		file::CheckDirectory(current_directory);

		//file::SetCurrentPath(global_path.string() + "/" + current_directory);
		myPlane1 = file::LoadSingleFile<std::shared_ptr<Cad2d_Plane>>(current_directory, verbose);
		TNB_CHECK_LOADED_FILE(myPlane1);
		file::SetCurrentPath(global_path.string());
	}

	void loadFiles()
	{
		loadPlane0();
		loadPlane1();

		loadTag = true;
	}

	TNB_SAVE_MULTI_FILES_FUN("results", Cad2d_Plane::extension, myPlanes);


	void execute(const std::string& name)
	{
		TNB_CHECK_LOADED;

		myPlanes = Cad2d_Boolean::Subtract(myPlane0, myPlane1, myTol);
		int i = 0;
		for (const auto& x : myPlanes)
		{
			x->SetIndex(++i);
			x->SetName(name);
		}

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is successfully performed!" << endl;
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

	void setGlobals(const module_t& mod)
	{
		// io functions [1/23/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [1/23/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short c)->void {setVerbose(c); }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {setTarget(i); }), "setTarget");
		mod->add(chaiscript::fun([](double tol)-> void {setTol(tol); }), "setTolerance");

		// operators [1/23/2023 Payvand]
		mod->add(chaiscript::fun([](const std::string& op)-> void {execute(op); }), "execute");
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
			Info << " This application is aimed to apply the subtract boolean to the planes." << endl << endl;

			Info << " - INPUTS: two *.pln file format which are saved in '0' and '1' directories." << endl
				<< " - OUTPUTS: a series of *.pln file formats in 'results' directory." << endl
				<< " - the 'Target' is set to 0 (plane 0) as a default value. So, if the plane 0" << endl
				<< "   is the target, don't need to set the 'Target'." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Operators: " << endl << endl
				<< " - execute(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setTarget(unsigned int);     - Target: 0, 1" << endl
				<< " - setTolerance(double) "
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneSubtractBoolean"));

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
}
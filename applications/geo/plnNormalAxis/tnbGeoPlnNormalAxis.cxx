#include <Geo_Serialization.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <gp_Ax1.hxx>

namespace tnbLib
{

	static std::shared_ptr<gp_Ax1> myAx;
	static std::shared_ptr<gp_Pln> myPlan;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static double myLoc = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setLoc(double x)
	{
		myLoc = x;
		if (verbose)
		{
			Info << endl
				<< " the loc. is set to: " << myLoc << endl;
		}
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadAxis()
	{
		checkFolder("axis");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\axis)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();

				myAx = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
				if (NOT myAx)
				{
					FatalErrorIn(FunctionSIG)
						<< "no axis has been found." << endl
						<< abort(FatalError);
				}
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();

			myAx = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
			if (NOT myAx)
			{
				FatalErrorIn(FunctionSIG)
					<< "no axis has been found." << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		loadTag = true;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myAx = file::LoadFile<std::shared_ptr<gp_Ax1>>(name + ".axis3d", verbose);
		if (NOT myAx)
		{
			FatalErrorIn(FunctionSIG)
				<< "no axis has been found." << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("axis"))
		{
			loadAxis();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".axis3d").string();
			loadFile(name);
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(myPlan, name + ".gpln", verbose);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		Dir3d dir = myAx->Direction();
		Pnt3d p0 = myAx->Location();

		Pnt3d du(dir.XYZ());

		Pnt3d p1 = p0 + myLoc * du;

		myPlan = std::make_shared<gp_Pln>(p1, dir);
		exeTag = true;
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](double x)-> void {setLoc(x); }), "setLoc");
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

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
			Info << " This application is aimed to create a Plane from an axis." << endl;
			Info << " - subdirectories: axis" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setLoc(x)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbGeoPlnNormalAxis"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}
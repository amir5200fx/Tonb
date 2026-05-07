#include <Geo_Serialization.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax1.hxx>

namespace tnbLib
{

	static Pnt3d myOrigin(0, 0, 0);
	static Dir3d myDir(1, 0, 0);

	static unsigned short verbose = 0;

	static auto exeTag = false;

	static std::shared_ptr<gp_Ax1> myAx;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setOrigin(const Pnt3d& theCoord)
	{
		myOrigin = theCoord;
		if (verbose)
		{
			Info << endl
				<< " the origin is set to: " << myOrigin << endl;
		}
	}

	void setDir(const Dir3d& theDir)
	{
		myDir = theDir;
		if (verbose)
		{
			Info << endl
				<< " the direction is set to: " << myDir << endl;
		}
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
		file::SaveTo(myAx, name + ".axis3d", verbose);
	}

	void execute()
	{
		myAx = std::make_shared<gp_Ax1>(myOrigin, myDir);

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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](const Pnt3d& c)-> void {setOrigin(c); }), "setOrigin");
		mod->add(chaiscript::fun([](const Dir3d& d)-> void {setDir(d); }), "setDirection");
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// operators [2/10/2023 Payvand]
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Pnt3d(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Dir3d(x, y, z); }), "createDirection");
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
			Info << " This application is aimed to create a three-dimensional axis." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setOrigin(Point)" << endl
				<< " - setDirection(Dir)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [Dir] createDirection(double, double, double)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbGeoAxis3d"));
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
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <Standard_Failure.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;
	static std::string extension = ".gpln";

	static std::shared_ptr<gp_Pln> myPlane;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void makePlane(const Pnt3d& thePoint, const Dir3d& theV)
	{
		try
		{
			myPlane = std::make_shared<gp_Pln>(thePoint, theV);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to create the plane: " << endl
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	void makePlane(const Standard_Real theA, const Standard_Real theB, const Standard_Real theC, const Standard_Real theD)
	{
		try
		{
			myPlane = std::make_shared<gp_Pln>(theA, theB, theC, theD);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to create the plane: " << endl
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT myPlane)
		{
			FatalErrorIn(FunctionSIG)
				<< "No plane has been found!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myPlane, name + extension, verbose);
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/21/2021 Amir]
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Pnt3d(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Dir3d(x, y, z); }), "createDirection");
		mod->add(chaiscript::fun([](const Pnt3d& theCoord, const Dir3d& theDir)-> void {makePlane(theCoord, theDir); }), "makePlane");
		mod->add(chaiscript::fun([](double a, double b, double c, double d)-> void {makePlane(a, b, c, d); }), "makePlane");
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
			Info << " This application is aimed to create a plane." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl
				<< " - [Point] createPoint(x, y, z)" << endl
				<< " - [Direction] createDirection(u, v, w)" << endl
				<< " - createPlane(Point, Direction)" << endl
				<< " - createPlane(A, B, C, D)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbGeoPlane"));

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
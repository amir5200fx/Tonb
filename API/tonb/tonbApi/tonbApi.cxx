#include <Cad_API.hxx>
#include <Geo_API.hxx>
#include <Global_Chaiscript.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	bool IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument == command;
	}

	void activate(const module_t mod)
	{
		chai::geo::functions(mod);
		chai::cad::functions(mod);
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
			Info << " This application is aimed to create a sphere." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl
				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [Direction] createDirection(double, double, double)" << endl
				<< " - [Ax] createCoordinateSystem(Point, main Direction, x-Direction)" << endl
				<< " - [Ax] createCoordinateSystem(Point, main Direction);     - x- and y-direction are defined automatically." << endl
				<< endl
				<< " - makeSphere(Point, radius, name [optional])" << endl
				<< " - makeSphere(Ax, radius, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, angle2, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, angle2, angle3, name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			auto address = file::GetSystemFile("tonbApi");
			fileName myFileName(address);

			try
			{
				auto mod = std::make_shared<chaiscript::Module>();
				activate(mod);

				//chai::obj.add(mod);

				chai::obj.eval_file(myFileName);
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
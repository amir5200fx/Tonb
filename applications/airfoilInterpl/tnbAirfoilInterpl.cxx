#include <Cad_GeomSurface.hxx>
#include <Cad_CurveTools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Pnt3d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Face.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>

namespace tnbLib
{

	static double spanLen = 1.0;
	static bool doubleSide = false;

	static unsigned short verbose = 0;
	static auto exeTag = false;
	static auto loadTag = false;

	std::shared_ptr<std::vector<Pnt3d>> myCoords;

	static std::shared_ptr<Cad_GeomSurface> mySurface;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setSpanLen(double x)
	{
		spanLen = x;
		if (verbose)
		{
			Info << endl
				<< " - the span length is set to: " << spanLen << endl;
		}
	}

	void setTwoSided(bool cond)
	{
		doubleSide = cond;
		if (verbose)
		{
			Info << endl
				<< " - the two sided condition is set to: " << (doubleSide ? "TRUE" : "FALSE") << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		std::ifstream file(name);
		if (file.is_open())
		{
			myCoords = std::make_shared<std::vector<Pnt3d>>();
			std::string line;
			while (std::getline(file, line))
			{
				std::istringstream iss(line);

				double x, y;
				if (iss >> x >> y)
				{
					myCoords->push_back({ x,y,0 });
				}
				else
				{
					FatalErrorIn(FunctionSIG)
						<< "Failed to extract two numbers from the line." << endl
						<< abort(FatalError);
				}
			}
			file.close();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Failed to open the file." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}
		file::SaveTo(mySurface, name + Cad_GeomSurface::extension, verbose);
	}

	void saveTo()
	{
		saveTo("");
	}

	void execute(const std::string& name)
	{
		if (NOT myCoords)
		{
			FatalErrorIn(FunctionSIG)
				<< "no offset points have been detected." << endl
				<< abort(FatalError);
		}

		auto curve =
			Cad_CurveTools::Interpolation(*myCoords);
		Handle(Geom_Surface) surface = new Geom_SurfaceOfLinearExtrusion(curve, gp::DZ());

		Handle(Geom_Surface) patch;
		if (doubleSide)
		{
			patch = new Geom_RectangularTrimmedSurface(surface, -0.5 * spanLen, 0.5 * spanLen, false);
		}
		else
		{
			patch = new Geom_RectangularTrimmedSurface(surface, 0, spanLen, false);
		}
		mySurface = std::make_shared<Cad_GeomSurface>(0, name, std::move(patch));
		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
		}
		exeTag = true;
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
		// io functions [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setSpanLen(x); }), "setSpanLength");
		mod->add(chaiscript::fun([](bool c)-> void {setTwoSided(c); }), "setTwoSided");

		// operators [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
		mod->add(chaiscript::fun([]()-> void {execute(""); }), "execute");
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
			Info << endl;
			Info << " This application is aimed to create a surface airfoil." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name)" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setSpanLenght(x)" << endl
				<< " - setTwoSided(cond);   cond : true, false" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbAirfoilInterpl"));

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
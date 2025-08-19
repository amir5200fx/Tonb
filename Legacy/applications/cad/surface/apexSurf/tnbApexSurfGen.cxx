#include <Cad_RailRevolve.hxx>
#include <Cad_GeomCurve.hxx>
#include <Cad_GeomSurface.hxx>
#include <Dir3d.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineSurface.hxx>
#include <Geom_BSplineCurve.hxx>

namespace tnbLib
{
	static const std::string saveExt = Cad_GeomSurface::extension;

	static std::shared_ptr<Cad_GeomCurve> myGeneratrix;
	static std::shared_ptr<Cad_GeomCurve> myRail;

	static std::shared_ptr<Cad_GeomSurface> mySurf;
	static std::shared_ptr<Cad_GeomSurface> myApex;

	static gp_Ax1 myAxis;
	static double myTol = 1.0e-6;

	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;
	static unsigned short verbose(0);

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setApexLoc(const Pnt3d& loc)
	{
		myAxis.SetLocation(loc);
		if (verbose)
		{
			Info << " - the apex location is set to: " << myAxis.Location() << endl;
		}
	}

	void setApexDir(const Dir3d& d)
	{
		myAxis.SetDirection(d);
		if (verbose)
		{
			Info << " - the apex direction is set to: " << myAxis.Direction() << endl;
		}
	}

	void setTol(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << " - the tolerance is set to: " << myTol << endl;
		}
	}

	void loadFile()
	{
		const auto currentPath = boost::filesystem::current_path().string();

		{//- loading generatrix curve
			if (NOT boost::filesystem::is_directory("generatrix"))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'generatrix' directory has been found!" << endl
					<< abort(FatalError);
			}

			//- change the current path
			boost::filesystem::current_path(currentPath + R"(\generatrix)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_GeomCurve::extension).string();

			myGeneratrix = file::LoadFile<std::shared_ptr<Cad_GeomCurve>>(name + Cad_GeomCurve::extension, verbose);
			if (NOT myGeneratrix)
			{
				FatalErrorIn(FunctionSIG)
					<< "the generatrix curve is null!" << endl
					<< abort(FatalError);
			}

			//- change the current path
			boost::filesystem::current_path(currentPath);
		}

		{//- loading generatrix curve
			if (NOT boost::filesystem::is_directory("rail"))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'rail' directory has been found!" << endl
					<< abort(FatalError);
			}

			//- change the current path
			boost::filesystem::current_path(currentPath + R"(\rail)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_GeomCurve::extension).string();

			myRail = file::LoadFile<std::shared_ptr<Cad_GeomCurve>>(name + Cad_GeomCurve::extension, verbose);
			if (NOT myRail)
			{
				FatalErrorIn(FunctionSIG)
					<< "the rail curve is null!" << endl
					<< abort(FatalError);
			}

			//- change the current path
			boost::filesystem::current_path(currentPath);
		}

		if (verbose)
		{
			Info << endl
				<< " - all curves have been loaded, successfully!" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myApex;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	void createPatch(const std::string& name)
	{
		auto patch = Handle(Geom_BSplineSurface)::DownCast(mySurf->Geometry());
		if (NOT patch)
		{
			FatalErrorIn(FunctionSIG)
				<< "no bspline surface has been detected!" << endl
				<< abort(FatalError);
		}

		auto alg = std::make_shared<Cad_RailRevolve>();

		alg->SetAxis(myAxis);
		alg->SetTolerance(myTol);
		alg->LoadGeneratrix(Handle(Geom_BSplineCurve)::DownCast(myGeneratrix->Geometry()));
		alg->LoadRail(Handle(Geom_BSplineCurve)::DownCast(myRail->Geometry()));

		alg->Perform();

		myApex = std::make_shared<Cad_GeomSurface>(0, name, alg->Patch());
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		createPatch("");

		exeTag = true;
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		createPatch(name);

		exeTag = true;
	}

	auto createPoint(double x, double y, double z)
	{
		return Pnt3d(x, y, z);
	}

	auto createDir(double x, double y, double z)
	{
		return Dir3d(x, y, z);
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
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](const Pnt3d& p)-> void {setApexLoc(p); }), "setApexLoc");
		mod->add(chaiscript::fun([](const Dir3d& d)-> void {setApexDir(d); }), "setApexDir");
		mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");

		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return createPoint(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return createDir(x, y, z); }), "createDirection");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute");
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
	FatalError.throwExceptions();

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
			Info << " This application is aimed to create an apex patch." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile()" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setApexLoc(Point)" << endl
				<< " - setApexDir(Direction)" << endl
				<< " - setTolerance(double)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [direction] createDirection(double, double, double)" << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);
	

			try
			{
				std::string address = ".\\system\\tnbApexSurfGen";
				fileName theFileName(address);

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
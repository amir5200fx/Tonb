#include <Cad_GeomCurve.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Dir2d.hxx>
#include <Pnt2d.hxx>
#include <Dir3d.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineCurve.hxx>
#include <Geom_Plane.hxx>
#include <gp_Pln.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

namespace tnbLib
{
	static const std::string saveExt = Cad_GeomCurve::extension;

	static unsigned short verbose(0);
	static bool exeTag = false;

	static Pnt3d loc0 = Pnt3d(0.0, 1.0, 0.0);
	static Pnt3d loc1 = Pnt3d(1.0, 0.0, 0.0);

	static Dir3d dir0 = Dir3d(1.0, 0.0, 0.0);
	static Dir3d dir1 = Dir3d(0.0, 1.0, 0.0);

	static double weight = 1.0;

	static std::shared_ptr<Cad_GeomCurve> myCurve;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setLoc0(const Pnt3d& p)
	{
		loc0 = p;
		if (verbose)
		{
			Info << endl
				<< " - the loc0 is set to: " << loc0 << endl;
		}
	}

	void setLoc1(const Pnt3d& p)
	{
		loc1 = p;
		if (verbose)
		{
			Info << endl
				<< " - the loc1 is set to: " << loc1 << endl;
		}
	}

	void setDir0(const Dir3d& d)
	{
		dir0 = d;
		if (verbose)
		{
			Info << endl
				<< " - the dir0 is set to: " << dir0 << endl;
		}
	}

	void setDir1(const Dir3d& d)
	{
		dir1 = d;
		if (verbose)
		{
			Info << endl
				<< " - the dir1 is set to: " << dir1 << endl;
		}
	}

	void setWeight(double x)
	{
		weight = x;
		if (verbose)
		{
			Info << endl
				<< " - the weight is set to: " << weight << endl;
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

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myCurve;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto createPlane(const Pnt3d& pt, const Dir3d& n)
	{
		gp_Pln pl(pt, n);

		Handle(Geom_Plane) pln = new Geom_Plane(pl);
		return std::move(pln);
	}

	auto CalcDir(const Entity_Segment<Pnt2d>& ent)
	{
		Dir2d dir(ent.P1(), ent.P0());
		return std::move(dir);
	}

	auto projectDir(const Dir3d& d, const Handle(Geom_Plane)& pln)
	{
		auto p0 = Pnt3d(0, 0, 0);
		auto p1 = Pnt3d(d.XYZ());

		auto e = CalcDir(Cad_Tools::Project(Entity_Segment<const Pnt3d&>(p0, p1), pln));
		return std::move(e);
	}

	void execute(const std::string& name)
	{
		try
		{
			auto n = dir0.Crossed(dir1);
			auto pln = createPlane(loc0, n);

			auto e0 = projectDir(dir0, pln);
			auto e1 = projectDir(dir1, pln);

			auto p0 = Cad_Tools::Project(loc0, pln);
			auto p1 = Cad_Tools::Project(loc1, pln);

			auto intP = Geo_Tools::IntersectionTwoLines(p0, e0, p1, e1, Precision::Angular());

			auto corner = pln->Value(intP.X(), intP.Y());

			TColgp_Array1OfPnt poles(1, 3);
			poles.SetValue(1, loc0);
			poles.SetValue(2, corner);
			poles.SetValue(3, loc1);

			TColStd_Array1OfReal weights(1, 3);
			weights.SetValue(1, 1.0);
			weights.SetValue(2, weight);
			weights.SetValue(3, 1.0);

			TColStd_Array1OfReal knots(1, 2);
			knots.SetValue(1, 0);
			knots.SetValue(2, 1);

			TColStd_Array1OfInteger mults(1, 2);
			mults.SetValue(1, 3);
			mults.SetValue(2, 3);

			Handle(Geom_BSplineCurve) curve = new Geom_BSplineCurve(poles, weights, knots, mults, 2);
			myCurve = std::make_shared<Cad_GeomCurve>(0, name, std::move(curve));
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}

		exeTag = true;
	}

	void execute()
	{
		execute("");
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

		//- IO functions:
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- Settings:
		mod->add(chaiscript::fun([](unsigned short c)->void {setVerbose(c); }), "setVerbose");

		mod->add(chaiscript::fun([](double x)-> void {setWeight(x); }), "setWeight");
		mod->add(chaiscript::fun([](const Pnt3d& p)-> void {setLoc0(p); }), "setLocation0");
		mod->add(chaiscript::fun([](const Pnt3d& p)-> void {setLoc1(p); }), "setLocation1");
		mod->add(chaiscript::fun([](const Dir3d& p)-> void {setDir0(p); }), "setDirection0");
		mod->add(chaiscript::fun([](const Dir3d& p)-> void {setDir1(p); }), "setDirection1");

		//- operators:
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Pnt3d(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z)-> auto {return Dir3d(x, y, z); }), "createDirection");
		mod->add(chaiscript::fun([]() ->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name) ->void {execute(name); }), "execute");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a conic curve." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setLocation0(Point)" << endl
				<< " - setLocation1(Point)" << endl
				<< " - setDirection0(Dir)" << endl
				<< " - setDirection1(Dir)" << endl << endl

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

			setGlobals(mod);

			chai.add(mod);

			try
			{
				std::string address = ".\\system\\tnbConicCurveGen";
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
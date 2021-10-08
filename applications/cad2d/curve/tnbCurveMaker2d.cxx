#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Vertex.hxx>
#include <Dir2d.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <gp_Ax2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Elips2d.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Parab2d.hxx>
#include <Geom2d_Curve.hxx>

#include <vector>

#include <boost/filesystem.hpp>

#define SetNameIndex(myName) (int)myCurves.size(), myName + std::to_string((int)myCurves.size())

namespace tnbLib
{

	typedef std::shared_ptr<Pln_Curve> curve_t;
	typedef std::shared_ptr<Pln_Edge> edge_t;

	//curve_t myCurve;

	static std::vector<curve_t> myCurves;

	static double intplTol = 1.0E-6;
	static double ringTol = Precision::Confusion();

	static unsigned short verbose(0);

	//- globals

	/*void checkCurve()
	{
		if (NOT myCurve)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been constructed!" << endl
				<< abort(FatalError);
		}
	}*/

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setIntplTol(double x)
	{
		intplTol = x;
	}

	void setName(const curve_t& c, const std::string& name)
	{
		c->SetName(name);
	}

	auto makePointList()
	{
		std::vector<Pnt2d> l;
		return std::move(l);
	}

	void pushBackToList(std::vector<Pnt2d>& l, const Pnt2d& p)
	{
		l.push_back(p);
	}

	auto getCurrentPath()
	{
		auto dir = boost::filesystem::current_path();
		return std::move(dir);
	}

	/*void removeAllSubdirectories()
	{
		boost::filesystem::
	}*/

	//- curve makers

	auto makeInterpolation(const std::vector<Pnt2d>& q)
	{
		auto geom = Pln_CurveTools::Interpolation(q, false, intplTol);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("interpl "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makePoint(double x, double y)
	{
		return Pnt2d(x, y);
	}

	auto makeDir(double x, double y)
	{
		return Dir2d(x, y);
	}

	auto makeVec(double x, double y)
	{
		return Vec2d(x, y);
	}

	auto makeAx(const Pnt2d& p, const Dir2d& v)
	{
		return gp_Ax2d(p, v);
	}

	auto makeGeoCircle(const gp_Ax2d& ax, double r)
	{
		gp_Circ2d g(ax, r);
		return std::move(g);
	}

	auto makeGeoEllips(const gp_Ax2d& ax, double rm, double r)
	{
		gp_Elips2d g(ax, rm, r);
		return std::move(g);
	}

	auto makeGeoHybr(const gp_Ax2d& ax, double rm, double r)
	{
		gp_Hypr2d g(ax, rm, r);
		return std::move(g);
	}

	auto makeGeoParb(const gp_Ax2d& mirror, double focal)
	{
		gp_Parab2d g(mirror, focal);
		return std::move(g);
	}

	auto makeGeoParb(const gp_Ax2d& directrix, const Pnt2d& focal)
	{
		gp_Parab2d g(directrix, focal);
		return std::move(g);
	}

	auto makeSegment(const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("segment "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircArc(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto geom = Pln_CurveTools::MakeCircArc(p0, p1, p2);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircArc(const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p2)
	{
		auto geom = Pln_CurveTools::MakeCircArc(p0, v0, p2);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircArc(const gp_Circ2d& c, double a0, double a1)
	{
		auto geom = Pln_CurveTools::MakeCircArc(c, a0, a1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircArc(const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeCircArc(c, p0, p1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeElipsArc(const gp_Elips2d& e, double a0, double a1)
	{
		auto geom = Pln_CurveTools::MakeElipsArc(e, a0, a1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("ellipse "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeElipsArc(const gp_Elips2d& e, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeElipsArc(e, p0, p1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("ellipse "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeHyprArc(const gp_Hypr2d& h, double a0, double a1)
	{
		auto geom = Pln_CurveTools::MakeHyprArc(h, a0, a1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("hyperbola "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeHyprArc(const gp_Hypr2d& h, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeHyprArc(h, p0, p1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("hyperbola "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeParbArc(const gp_Parab2d& p, double a0, double a1)
	{
		auto geom = Pln_CurveTools::MakeParbArc(p, a0, a1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("parabola "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeParbArc(const gp_Parab2d& p, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeParbArc(p, p0, p1);
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("parabola "), std::move(geom));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircle(const gp_Circ2d& C)
	{
		auto geom = Pln_CurveTools::MakeCircle(C);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto geom = Pln_CurveTools::MakeCircle(p0, p1, p2);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircle(const Pnt2d& p0, double r)
	{
		auto geom = Pln_CurveTools::MakeCircle(p0, r);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeCircle(const Pnt2d& c, const Pnt2d& p)
	{
		auto geom = Pln_CurveTools::MakeCircle(c, p);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("circle "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeEllipse(const gp_Elips2d& E)
	{
		auto geom = Pln_CurveTools::MakeEllipse(E);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("ellipse "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	auto makeEllipse(const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)
	{
		auto geom = Pln_CurveTools::MakeEllipse(s0, s1, c);
		auto trimmed = Pln_CurveTools::Trim(geom, geom->FirstParameter(), geom->LastParameter());
		auto myCurve = std::make_shared<Pln_Curve>(SetNameIndex("ellipse "), std::move(trimmed));
		myCurves.push_back(myCurve);

		if (verbose)
		{
			Info << " - a curve, id: " << myCurve->Index() << ", name: " << myCurve->Name() << ", is created, successfully!" << endl;
		}
		return myCurve;
	}

	void saveTo(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
		}

		auto myEdges = Pln_Tools::RetrieveEdges(myCurves);

		size_t i = 0;
		for (const auto& x : myEdges)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << x;

			if (verbose)
			{
				Info << " - curve, id:  " << x->Index() << ", name: " << x->Name() << "is saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}

		if (verbose)
		{
			Info << endl
				<< " all curves are saved, successfully!" << endl;
		}
	}

	/*void loadCurve(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive oa(f);

		oa >> myCurve;
	}*/
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
		mod->add(chaiscript::fun([](const curve_t& c, const std::string& name)-> void {setName(c, name); }), "setName");
		mod->add(chaiscript::fun([](double x)->void {setIntplTol(x); }), "setInterplTol");
		mod->add(chaiscript::fun([]()->auto {return makePointList(); }), "makePointList");
		mod->add(chaiscript::fun([](std::vector<Pnt2d>& l, const Pnt2d& p)->void {pushBackToList(l, p); }), "pushBack");

		mod->add(chaiscript::fun([](const std::vector<Pnt2d>& Q)->void {makeInterpolation(Q); }), "makeInterpolation");

		mod->add(chaiscript::fun([](double x, double y)-> auto {return makePoint(x, y); }), "makePoint");
		mod->add(chaiscript::fun([](double x, double y)-> auto {return makeDir(x, y); }), "makeDirection");

		mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& d)-> auto {return makeAx(p, d); }), "makeAxis");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, double r)-> auto {return makeGeoCircle(ax, r); }), "makeGeoCircle");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, double rm, double r)-> auto {return makeGeoEllips(ax, rm, r); }), "makeGeoEllips");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, double rm, double r)-> auto {return makeGeoHybr(ax, rm, r); }), "makeGeoHybr");
		mod->add(chaiscript::fun([](const gp_Ax2d& mirror, double focal)-> auto {return makeGeoParb(mirror, focal); }), "makeGeoParab");
		mod->add(chaiscript::fun([](const gp_Ax2d& directrix, const Pnt2d& focal)-> auto {return makeGeoParb(directrix, focal); }), "makeGeoParab");

		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeSegment(p0, p1); }), "makeSegment");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircArc(p0, p1, p2); }), "makeCircArc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p2)-> auto {return makeCircArc(p0, v0, p2); }), "makeCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, double a0, double a1)-> auto {return makeCircArc(c, a0, a1); }), "makeCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeCircArc(c, p0, p1); }), "makeCircArc");

		mod->add(chaiscript::fun([](const gp_Elips2d& c, double a0, double a1)-> auto {return makeElipsArc(c, a0, a1); }), "makeElipsArc");
		mod->add(chaiscript::fun([](const gp_Elips2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeElipsArc(c, p0, p1); }), "makeElipsArc");

		mod->add(chaiscript::fun([](const gp_Hypr2d& c, double a0, double a1)-> auto {return makeHyprArc(c, a0, a1); }), "makeHyprArc");
		mod->add(chaiscript::fun([](const gp_Hypr2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeHyprArc(c, p0, p1); }), "makeHyprArc");

		mod->add(chaiscript::fun([](const gp_Parab2d& c, double a0, double a1)-> auto {return makeParbArc(c, a0, a1); }), "makeParbArc");
		mod->add(chaiscript::fun([](const gp_Parab2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeParbArc(c, p0, p1); }), "makeParbArc");

		mod->add(chaiscript::fun([](const gp_Circ2d& c)-> auto {return makeCircle(c); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircle(p0, p1, p2); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, double r)-> auto {return makeCircle(p0, r); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& c, const Pnt2d& p)-> auto {return makeCircle(c, p); }), "makeCircle");

		mod->add(chaiscript::fun([](const gp_Elips2d& c)-> auto {return makeEllipse(c); }), "makeElips");
		mod->add(chaiscript::fun([](const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)-> auto {return makeEllipse(s0, s1, c); }), "makeElips");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](unsigned short c)-> void {setVerbose(c); }), "setVerbose");
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
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a list of planar curve." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - saveTo(string)" << endl << endl

				<< " # geometric operators: " << endl << endl
				<< " - [point]     makePoint(x, y) " << endl
				<< " - [direction] makeDirection(x,y) " << endl
				<< " - [axis]      makeAxis(point, direction) " << endl << endl

				<< " - [geo circle] makeGeoCircle(axis, radius) " << endl
				<< " - [geo ellips] makeGeoEllips(axis, radius1, radius2);    radius1 >= radius2" << endl
				<< " - [geo hybr]   makeGeoHybr(axis, radius1, radius2);      radius1 >= radius2 " << endl
				<< " - [geo parab]  makeGeoParab(axis, focal) " << endl
				<< " - [geo parab]  makeGeoParab(directrix axis, focal point) " << endl << endl << endl

				<< " # curve makers: " << endl << endl
				
				<< " - [curve] makeSegment(point, point)" << endl <<endl

				<< " - [curve] makeCircArc(point, point, point)" << endl
				<< " - [curve] makeCircArc(point0, vector0, point1)" << endl
				<< " - [curve] makeCircArc(geoCircle, double a0, double a1)" << endl
				<< " - [curve] makeCircArc(geoCircle, point p0, point p1)" << endl << endl

				<< " - [curve] makeElipsArc(geoEllips, double a0, double a1)" << endl
				<< " - [curve] makeElipsArc(geoEllips, double a0, double a1)" << endl << endl

				<< " - [curve] makeHyprArc(geoHypr, double a0, double a1)" << endl
				<< " - [curve] makeHyprArc(geoHypr, double a0, double a1)" << endl << endl

				<< " - [curve] makeParbArc(geoParab, double a0, double a1)" << endl
				<< " - [curve] makeParbArc(geoParab, double a0, double a1)" << endl << endl

				<< " - [curve] makeCircle(geoCircle)" << endl
				<< " - [curve] makeCircle(point p0, point p1, point p2)" << endl
				<< " - [curve] makeCircle(point p0, radius)" << endl
				<< " - [curve] makeCircle(centre point, point)" << endl << endl

				<< " - [curve] makeElips(geoEllips)" << endl
				<< " - [curve] makeElips(point s0, point s1, point c)" << endl << endl

				<< " - [curve] makeInterpolation(point list)" << endl

				<< " # Global functions: " << endl << endl

				<< " - [point list] makePointList()" << endl
				<< " - setInterplTol(double)" << endl
				<< " - (pointList).pushBack(point)" << endl
				<< " - (curve).SetName(string)" << endl
				<< " - setVerbose(int)" << endl

				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbCurveMaker2d";
			fileName myFileName(address);

			try
			{
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
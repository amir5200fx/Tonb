#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler.hxx>
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

namespace tnbLib
{

	typedef std::shared_ptr<Pln_Curve> curve_t;
	typedef std::shared_ptr<Pln_Edge> edge_t;
	typedef std::shared_ptr<Cad2d_Plane> plane_t;

	static plane_t myPlane;
	static gp_Ax2 mySys = gp::XOY();

	static std::vector<edge_t> myCurves;
	static auto myModeler = std::make_shared<Cad2d_Modeler>();

	static unsigned short verbose = 0;

	static double ringTol = Precision::Confusion();

	void checkPlane()
	{
		if (NOT myPlane)
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been constructed!" << endl
				<< abort(FatalError);
		}
	}

	void loadCurves(const std::string& name)
	{
		std::fstream file;
		file.open(name, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		TNB_iARCH_FILE_TYPE ia(file);

		ia >> myCurves;

		if (verbose)
		{
			Info << myCurves.size() << " edge(s) has(have) been loaded." << endl;
		}
	}

	auto makeEdge(curve_t&& c)
	{
		if (c->IsRing(ringTol))
		{
			auto vtx = std::make_shared<Pln_Vertex>(c->FirstCoord());
			std::shared_ptr<Pln_Edge> ring = std::make_shared<Pln_Ring>(0, "ring", vtx, std::move(c));
			return std::move(ring);
		}
		else
		{
			auto v0 = std::make_shared<Pln_Vertex>(c->FirstCoord());
			auto v1 = std::make_shared<Pln_Vertex>(c->LastCoord());
			auto edge = std::make_shared<Pln_Edge>(std::move(v0), std::move(v1), std::move(c));
			return std::move(edge);
		}
	}

	void makePlane()
	{
		if (myCurves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no edge has been detected!" << endl
				<< abort(FatalError);
		}

		myModeler->Import(myCurves);

		Cad2d_Modeler::selctList l;
		myModeler->SelectAll(l);
		myModeler->MakePlanes(l);

		if (myModeler->NbPlanes() > 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "no multiple planes construction is permitted" << endl
				<< abort(FatalError);
		}

		if (NOT myModeler->NbPlanes())
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been created" << endl
				<< abort(FatalError);
		}
		auto iter = myModeler->Planes().begin();
		myPlane = std::move(iter->second);
	}

	//- geometric makers

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

	void makeBox(const Pnt2d& p0, const Pnt2d& p1)
	{
		myPlane = Cad2d_Plane::MakeBox(p0, p1, mySys);
	}

	void makeBox(const gp_Ax2d& ax, double dx, double dy)
	{
		myPlane = Cad2d_Plane::MakeBox(ax, dx, dy, mySys);
	}

	void makeBox(const Pnt2d& p0, double dx, double dy)
	{
		myPlane = Cad2d_Plane::MakeBox(p0, dx, dy, mySys);
	}

	void makeCircle(const gp_Circ2d& c)
	{
		myPlane = Cad2d_Plane::MakeCircle(c, mySys);
	}

	void makeCircle(const gp_Circ2d& c, const Pnt2d& p)
	{
		myPlane = Cad2d_Plane::MakeCircle(c, p, mySys);
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		myPlane = Cad2d_Plane::MakeCircle(p0, p1, p2, mySys);
	}

	void makeCircle(const Pnt2d& p0, double r)
	{
		myPlane = Cad2d_Plane::MakeCircle(p0, r, mySys);
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1)
	{
		myPlane = Cad2d_Plane::MakeCircle(p0, p1, mySys);
	}

	void makeEllipse(const gp_Elips2d& e)
	{
		myPlane = Cad2d_Plane::MakeEllipse(e, mySys);
	}

	void makeEllipse(const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& centre)
	{
		myPlane = Cad2d_Plane::MakeEllipse(s0, s1, centre, mySys);
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myPlane;
	}

	void exportToPlt(const std::string& name)
	{
		checkPlane();

		fileName fn(name);
		OFstream f(fn);
		myPlane->ExportToPlt(f);
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
		mod->add(chaiscript::fun([]()->void {makePlane(); }), "execute");

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCurves(name); }), "loadCurves");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(name); }), "drawToPlt");

		mod->add(chaiscript::fun([](unsigned short c)-> void {verbose = c; Cad2d_Modeler::verbose = c; }), "setVerbose");
	}

	void setGeometrics(const module_t& mod)
	{
		mod->add(chaiscript::fun([](double x, double y)->auto {auto t = makePoint(x, y); return std::move(t); }), "makePoint");
		mod->add(chaiscript::fun([](double x, double y)->auto {auto t = makeDir(x, y); return std::move(t); }), "makeDirection");
		mod->add(chaiscript::fun([](double x, double y)->auto {auto t = makeVec(x, y); return std::move(t); }), "makeVector");
		mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& d)->auto {auto t = makeAx(p, d); return std::move(t); }), "makeAxis");

		mod->add(chaiscript::fun([](const gp_Ax2d& theAx, double r)->auto {auto t = makeGeoCircle(theAx, r); return std::move(t); }), "makeGeoCircle");
		mod->add(chaiscript::fun([](const gp_Ax2d& theAx, double rm, double r)->auto {auto t = makeGeoEllips(theAx, rm, r); return std::move(t); }), "makeGeoEllipse");
	}

	void setMakers(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeBox(p0, p1); }), "makeBox");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, double dx, double dy)-> void {makeBox(ax, dx, dy); }), "makeBox");
		mod->add(chaiscript::fun([](const Pnt2d& p0, double dx, double dy)-> void {makeBox(p0, dx, dy); }), "makeBox");

		mod->add(chaiscript::fun([](const gp_Circ2d& c)-> void {makeCircle(c); }), "makeCircle");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p)-> void {makeCircle(c, p); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> void {makeCircle(p0, p1, p2); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, double r)-> void {makeCircle(p0, r); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeCircle(p0, p1); }), "makeCircle");

		mod->add(chaiscript::fun([](const gp_Elips2d& c)-> void {makeEllipse(c); }), "makeEllipse");
		mod->add(chaiscript::fun([](const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& centre)-> void {makeEllipse(s0, s1, centre); }), "makeEllipse");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setGeometrics(mod);
			setMakers(mod);

			chai.add(mod);

			fileName myFileName("plane");

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
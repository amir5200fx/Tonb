#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Modeler_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Tools.hxx>
#include <Bnd_Box2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>

#include <gp_Circ2d.hxx>
#include <gp_Elips2d.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Parab2d.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Pln_Edge> edge_t;
	typedef cad2dLib::Modeler_Tools tools;
	typedef std::shared_ptr<Cad2d_Modeler> modeler_t;
	typedef cad2dLib::Modeler_SelectList selList;
	typedef std::shared_ptr<Geo_ApprxCurve_Info> GeoApxCurveInfo_t;

	static const auto modeler = std::make_shared<Cad2d_Modeler>();
	static const auto disctInfo = std::make_shared<Geo_ApprxCurve_Info>();
	static selList selt;

	//
	//- set the discretization parameters
	//
	void setApprox(const GeoApxCurveInfo_t& par, const double apx)
	{
		par->SetApprox(apx);
	}

	void setAngle(const GeoApxCurveInfo_t& par, const double angl)
	{
		par->SetAngle(angl);
	}

	void setMinSize(const GeoApxCurveInfo_t& par, const double minSize)
	{
		par->SetMinSize(minSize);
	}

	void setMaxNbSubdivision(const GeoApxCurveInfo_t& par, const int n)
	{
		par->SetMaxNbSubdivision(n);
	}

	void setInitNbSubdivision(const GeoApxCurveInfo_t& par, const int n)
	{
		par->SetInitNbSubdivision(n);
	}

	void setNbSamples(const GeoApxCurveInfo_t& par, const int n)
	{
		par->SetNbSamples(n);
	}

	void setDefault(const GeoApxCurveInfo_t& par)
	{
		par->SetApprox(Geo_ApprxCurve_Info::DEFAULT_APPROX);
		par->SetAngle(Geo_ApprxCurve_Info::DEFAULT_ANGLE);
		par->SetMinSize(Geo_ApprxCurve_Info::DEFAULT_MIN_SIZE);

		par->SetMaxNbSubdivision(Geo_ApprxCurve_Info::DEFAULT_MAX_NB_SUBDIVIDE);
		par->SetInitNbSubdivision(Geo_ApprxCurve_Info::DEFAULT_INIT_NB_SUBDIVIDE);
		par->SetNbSamples(Geo_ApprxCurve_Info::DEFAULT_NB_SAMPLES);
	}
	
	//- end of the discretization parameters

	auto boundingBox(const edge_t& e)
	{
		auto b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(e->Curve()->Geometry()));
		return std::move(b);
	}

	auto diaSize(const edge_t& e)
	{
		auto b = boundingBox(e);
		return b.Diameter();
	}

	void discretizationCurve(const edge_t& e)
	{
		e->Approx(disctInfo);
	}

	void autoDiscretization(const edge_t& e, const double tol)
	{
		auto d = diaSize(e);
		setMinSize(disctInfo, d*tol);
		discretizationCurve(e);
	}

	const auto& getDiscretization(const edge_t& e)
	{
		return e->Mesh();
	}
	
	//*******************************

	const auto& getModeler()
	{
		return modeler;
	}

	auto makePoint(const double x, const double y)
	{
		Pnt2d pt(x, y);
		return std::move(pt);
	}

	auto makeGeoAx2d(const Pnt2d& p, const Dir2d& v)
	{
		gp_Ax2d Ax2d(p, v);
		return std::move(Ax2d);
	}

	auto makeGeoAx22d(const Pnt2d& p, const Dir2d& vx, const Dir2d& vy)
	{
		gp_Ax22d Ax22d(p, vx, vy);
		return std::move(Ax22d);
	}

	auto makeGeoAx22d(const Pnt2d& p, const Dir2d& v, const bool s)
	{
		gp_Ax22d Ax22d(p, v, s);
		return std::move(Ax22d);
	}

	auto makeGeoAx22d(const gp_Ax2d& ax, const bool s)
	{
		gp_Ax22d Ax22d(ax, s);
		return std::move(Ax22d);
	}

	auto makeGeoCirc(const gp_Ax2d& ax, const double r, const bool s)
	{
		gp_Circ2d c(ax, r, s);
		return std::move(c);
	}

	auto makeGeoCirc(const gp_Ax2d& ax, const double r)
	{
		gp_Circ2d c(ax, r);
		return std::move(c);
	}

	auto makeGeoElips(const gp_Ax2d& ax, const double mjrR, const double mnrR, const bool s)
	{
		gp_Elips2d e(ax, mjrR, mnrR, s);
		return std::move(e);
	}

	auto makeGeoElips(const gp_Ax2d& ax, const double mjrR, const double mnrR)
	{
		gp_Elips2d e(ax, mjrR, mnrR);
		return std::move(e);
	}

	auto makeGeoHypr(const gp_Ax2d& ax, const double mjrR, const double mnrR, const bool s)
	{
		gp_Hypr2d hyp(ax, mjrR, mnrR, s);
		return std::move(hyp);
	}

	auto makeGeoHypr(const gp_Ax22d& axay, const double mjrR, const double mnrR)
	{
		gp_Hypr2d hyp(axay, mjrR, mnrR);
		return std::move(hyp);
	}

	auto makeGeoParab(const gp_Ax2d& ax, const double focal, const bool s)
	{
		gp_Parab2d parab(ax, focal, s);
		return std::move(parab);
	}

	auto makeGeoParab(const gp_Ax22d& axay, const double focalL)
	{
		gp_Parab2d parab(axay, focalL);
		return std::move(parab);
	}

	auto makeGeoParab(const gp_Ax2d& directrix, const gp_Pnt2d& focus, const bool s)
	{
		gp_Parab2d parab(directrix, focus, s);
		return std::move(parab);
	}

	
	//****************************************************************//

	void print(const Pnt2d& p)
	{
		Info << p << endl;
	}

	auto makeSegment(const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeSegment(p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(std::move(item))));
		return std::move(t);
	}

	auto makeSegment(const Pnt2d& p0, const double angl, const double L)
	{
		auto item = cad2dLib::Modeler_Tools::MakeSegment(p0, angl, L);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(p0, p1, p2);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const Pnt2d& p0, const Vec2d& v, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(p0, v, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const gp_Circ2d& c, const double ang0, const double ang1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(c, ang0, ang1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(c, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeElipsArc(const gp_Elips2d& el, const double ang0, const double ang1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeElipsArc(el, ang0, ang1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeElipsArc(const gp_Elips2d& el, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeElipsArc(el, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeHyperArc(const gp_Hypr2d& hr, const double ang0, const double ang1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeHyprArc(hr, ang0, ang1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeHyperArc(const gp_Hypr2d& hr, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeHyprArc(hr, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeParabArc(const gp_Parab2d& pr, const double ang0, const double ang1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeParbArc(pr, ang0, ang1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeParabArc(const gp_Parab2d& pr, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeParabArc(pr, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const gp_Circ2d& c)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(c);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const gp_Circ2d& c, const Pnt2d& p)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(c, p);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(p0, p1, p2);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& p, const double r)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(p, r);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& c, const Pnt2d& p)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(c, p);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeEllipse(const gp_Elips2d& el)
	{
		auto item = cad2dLib::Modeler_Tools::MakeEllipse(el);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeEllipse(const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)
	{
		auto item = cad2dLib::Modeler_Tools::MakeEllipse(s0, s1, c);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	/*void makeRectangular(const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeRectangular(p0, p1);
		getModeler()->Import(std::move(item));
	}

	void makeRectangular(const gp_Ax2d& ax, const double dx, const double dy)
	{
		auto item = cad2dLib::Modeler_Tools::MakeRectangular(ax, dx, dy);
		getModeler()->Import(std::move(item));
	}*/

	//****************************************************************//

	auto makeTransform()
	{
		gp_Trsf2d t;
		return std::move(t);
	}

	auto makeDirection(const Standard_Real x, const Standard_Real y)
	{
		Dir2d dir(x, y);
		return std::move(dir);
	}

	/*auto makePlane(const modeler_t& m)
	{
		return makePlane(m, selt);
	}*/

	auto makePlane(const modeler_t& m, selList& l)
	{
		return m->MakePlane(l);
	}

	void makePlanes(const modeler_t& m)
	{
		m->MakePlanes(selt);
	}
	
	//********************************************************************//


	void setMirror(gp_Trsf2d& t, const Pnt2d& p)
	{
		t.SetMirror(p);
	}

	void setRotation(gp_Trsf2d& t, const Pnt2d& p, const Standard_Real ang)
	{
		t.SetRotation(p, ang);
	}

	void setScale(gp_Trsf2d& t, const Pnt2d& p, const Standard_Real s)
	{
		t.SetScale(p, s);
	}

	void setTransformation(gp_Trsf2d& t, const gp_Ax2d& s0, const gp_Ax2d& s1)
	{
		t.SetTransformation(s0, s1);
	}

	void setTranslation(gp_Trsf2d& t, const Vec2d& v)
	{
		t.SetTranslation(v);
	}

	void setTranslation(gp_Trsf2d& t, const Pnt2d& p0, const Pnt2d& p1)
	{
		t.SetTranslation(p0, p1);
	}

	void setScaleFactor(gp_Trsf2d& t, const Standard_Real s)
	{
		t.SetScaleFactor(s);
	}

	void invert(gp_Trsf2d& t)
	{
		t.Invert();
	}
	
	auto selectEdge(const modeler_t& m, const Standard_Integer id)
	{
		auto t = m->SelectEdge(id);
		return std::move(t);
	}

	void removeEdge(const modeler_t& m, const edge_t& e)
	{
		m->RemoveEdge(e);
	}

	void selectList(const modeler_t& m, const Standard_Integer id, selList& l)
	{
		auto item = selectEdge(m, id);
		if (NOT m->HasDuplication(item, l)) m->Select(item, l);
	}

	void selectList(const modeler_t& m, const Standard_Integer id)
	{
		auto item = selectEdge(m, id);
		if (NOT m->HasDuplication(item, selt)) m->Select(item, selt);
	}

	void selectAllList(const modeler_t& m, selList& l)
	{
		m->SelectAll(l);
	}

	void selectAllList(const modeler_t& m)
	{
		m->SelectAll(selt);
	}

	void deSelectAllList(const modeler_t& m, selList& l)
	{
		m->deSelectAll(l);
	}

	void deSelectAllList(const modeler_t& m)
	{
		m->deSelectAll(selt);
	}

	void deSelectFromList(const modeler_t& m, const edge_t& e, selList& l)
	{
		m->deSelect(e, l);
	}

	void deSelectFromList(const modeler_t& m, const edge_t& e)
	{
		deSelectFromList(m, e, selt);
	}

	void unionOp(const modeler_t& m, const int pl0, const int pl1)
	{
		m->Union(pl0, pl1);
	}

	void subtOp(const modeler_t& m, const int pln0, const int pln1)
	{
		m->Subtract(pln0, pln1);
	}

	void intrsctOp(const modeler_t& m, const int pln0, const int pln1)
	{
		m->Intersection(pln0, pln1);
	}

	void exportToPlt(const edge_t& e, const fileName& name)
	{
		OFstream f(name);
		if (e->Mesh())
		{
			e->Mesh()->ExportToPlt(f);
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

	void addTypes(const module_t& t)
	{
		t->add(chaiscript::user_type<Pnt2d>(), "gPnt");
		t->add(chaiscript::user_type<gp_Circ2d>(), "gCirc");
		t->add(chaiscript::user_type<gp_Elips2d>(), "gElips");
		t->add(chaiscript::user_type<gp_Hypr2d>(), "gHypr");
		t->add(chaiscript::user_type<gp_Parab2d>(), "gParab");

		t->add(chaiscript::user_type<gp_Trsf2d>(), "gTrsf");

		t->add(chaiscript::user_type<Pln_Edge>(), "edge");
	}

	void setTransforms(const module_t& mod)
	{
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Pnt2d& p) { setMirror(t, p); }), "setMirror");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Pnt2d& p, const Standard_Real ang) { setRotation(t, p, ang); }), "setRotation");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Pnt2d& p, const Standard_Real s) { setScale(t, p, s); }), "setScale");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const gp_Ax2d& s0, const gp_Ax2d& s1) { setTransformation(t, s0, s1); }), "setTransformation");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Vec2d& v) { setTranslation(t, v); }), "setTranslation");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Pnt2d& p0, const Pnt2d& p1) { setTranslation(t, p0, p1); }), "setTranslation");
		mod->add(chaiscript::fun([](gp_Trsf2d& t, const Standard_Real s) { setScaleFactor(t, s); }), "setScaleFactor");
		mod->add(chaiscript::fun([](gp_Trsf2d& t) { invert(t); }), "invert");
	}

	void setOps(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const modeler_t& m, const int id)-> edge_t {auto t = selectEdge(m, id); return std::move(t); }), "selectEdge");
		mod->add(chaiscript::fun([](const modeler_t& m, const edge_t& e)-> void {removeEdge(m, e); }), "removeEdge");
		mod->add(chaiscript::fun([](const modeler_t& m, const int id)-> void {selectList(m, id); }), "addToSelectList");
		mod->add(chaiscript::fun([](const modeler_t& m, const edge_t& e)-> void {deSelectFromList(m, e); }), "removeFromSelectList");
		mod->add(chaiscript::fun([](const modeler_t& m)-> void {selectAllList(m); }), "selectAll");
		mod->add(chaiscript::fun([](const modeler_t& m)-> void {deSelectAllList(m); }), "deSelectAll");
		//mod->add(chaiscript::fun([](const modeler_t& m)-> int {return makePlane(m); }), "createPlane");
	}

	void setBooleans(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {unionOp(m, pl0, pl1); }), "union");
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {subtOp(m, pl0, pl1); }), "subtract");
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {intrsctOp(m, pl0, pl1); }), "intersection");
	}

	void setGeoFuncs(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const double x, const double y)-> auto {return makePoint(x, y); }), "MakePnt");

		mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& v)-> auto {return makeGeoAx2d(p, v); }), "MakeAxis");

		mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& vx, const Dir2d& vy)-> auto {return makeGeoAx22d(p, vx, vy); }), "MakeCoordSys");
		mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& v, const bool s)-> auto {return makeGeoAx22d(p, v, s); }), "MakeCoordSys");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const bool s)-> auto {return makeGeoAx22d(ax, s); }), "MakeCoordSys");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double r, const bool s)-> auto {return makeGeoCirc(ax, r, s); }), "MakeGeoCirc");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double r)-> auto {return makeGeoCirc(ax, r); }), "MakeGeoCirc");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double mjrR, const double mnrR, const bool s)-> auto {return makeGeoElips(ax, mjrR, mnrR, s); }), "MakeGeoElips");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double mjrR, const double mnrR)-> auto {return makeGeoElips(ax, mjrR, mnrR); }), "MakeGeoElips");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double mjrR, const double mnrR, const bool s)-> auto {return makeGeoHypr(ax, mjrR, mnrR, s); }), "makeGeoHypr");
		mod->add(chaiscript::fun([](const gp_Ax22d& axay, const double mjrR, const double mnrR)-> auto {return makeGeoHypr(axay, mjrR, mnrR); }), "makeGeoHypr");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double focal, const bool s)-> auto {return makeGeoParab(ax, focal, s); }), "makeGeoParab");
		mod->add(chaiscript::fun([](const gp_Ax22d& axay, const double focalL)-> auto {return makeGeoParab(axay, focalL); }), "makeGeoParab");
		mod->add(chaiscript::fun([](const gp_Ax2d& directrix, const gp_Pnt2d& focus, const bool s)-> auto {return makeGeoParab(directrix, focus, s); }), "makeGeoParab");
	}

	void setFuncs(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeSegment(p0, p1); }), "makeSegment");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const double ang, const double len)-> auto {return makeSegment(p0, ang, len); }), "makeSegment");

		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircArc(p0, p1, p2); }), "makeCircArc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Vec2d& v, const Pnt2d& p1)-> auto {return makeCircArc(p0, v, p1); }), "makeCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const double ang0, const double ang1)-> auto {return makeCircArc(c, ang0, ang1); }), "makeCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeCircArc(c, p0, p1); }), "makeCircArc");

		mod->add(chaiscript::fun([](const gp_Elips2d& el, const double ang0, const double ang1)-> auto {return makeElipsArc(el, ang0, ang1); }), "makeElipsArc");
		mod->add(chaiscript::fun([](const gp_Elips2d& el, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeElipsArc(el, p0, p1); }), "makeElipsArc");

		mod->add(chaiscript::fun([](const gp_Hypr2d& hr, const double ang0, const double ang1)-> auto {return makeHyperArc(hr, ang0, ang1); }), "makeHyprArc");
		mod->add(chaiscript::fun([](const gp_Hypr2d& hr, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeHyperArc(hr, p0, p1); }), "makeHyprArc");

		mod->add(chaiscript::fun([](const gp_Parab2d& pr, const double ang0, const double ang1)-> auto {return makeParabArc(pr, ang0, ang1); }), "makeParabArc");
		mod->add(chaiscript::fun([](const gp_Parab2d& pr, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeParabArc(pr, p0, p1); }), "makeParabArc");

		mod->add(chaiscript::fun([](const gp_Circ2d& c)-> auto {return makeCircle(c); }), "makeCirc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p)-> auto {return makeCircle(c, p); }), "makeCirc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircle(p0, p1, p2); }), "makeCirc");
		mod->add(chaiscript::fun([](const Pnt2d& p, const double r)-> auto {return makeCircle(p, r); }), "makeCirc");
		mod->add(chaiscript::fun([](const Pnt2d& c, const Pnt2d& p)-> auto {return makeCircle(c, p); }), "makeCirc");

		mod->add(chaiscript::fun([](const gp_Elips2d& el)-> auto {return makeEllipse(el); }), "makeElips");
		mod->add(chaiscript::fun([](const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)-> auto {return makeEllipse(s0, s1, c); }), "makeElips");

		//mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeRectangular(p0, p1); }), "makeRectangular");
		//mod->add(chaiscript::fun([](const gp_Ax2d& ax, const double dx, const double dy)-> void {makeRectangular(ax, dx, dy); }), "makeRectangular");

	}

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const Pnt2d& p)-> void {print(p); }), "print");
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

int main(int  argc, char *argv[])
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

			setGeoFuncs(mod);
			setFuncs(mod);

			setGlobals(mod);
			setTransforms(mod);
			setOps(mod);
			setBooleans(mod);

			chai.add(mod);

			fileName myFileName("modeler");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}
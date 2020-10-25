#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Pln_Ring.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Modeler_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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

	static selList selt;

	auto makePoint(const Standard_Real x, const Standard_Real y)
	{
		Pnt2d pt(x, y);
		return std::move(pt);
	}

	auto makeTransform()
	{
		gp_Trsf2d t;
		return std::move(t);
	}

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

	auto makeDirection(const Standard_Real x, const Standard_Real y)
	{
		Dir2d dir(x, y);
		return std::move(dir);
	}

	auto makeAxis(const Pnt2d& p, const Dir2d& d)
	{
		gp_Ax2d ax(p, d);
		return std::move(ax);
	}

	auto makeGeoCirc(const gp_Ax2d& ax, const Standard_Real r)
	{
		gp_Circ2d c(ax, r);
		return std::move(c);
	}

	auto makeGeoElips(const gp_Ax2d& ax, const Standard_Real majR, const Standard_Real minR)
	{
		gp_Elips2d e(ax, majR, minR);
		return std::move(e);
	}

	auto makeGeoHypr(const gp_Ax2d& ax, const Standard_Real majR, const Standard_Real minR)
	{
		gp_Hypr2d h(ax, majR, minR);
		return std::move(h);
	}

	auto makeGeoParab(const gp_Ax2d& ax, const Standard_Real focal)
	{
		gp_Parab2d p(ax, focal);
		return std::move(p);
	}

	auto makeSegment(const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto t = tools::MakeSegment(p0, p1);
		return m->Import(std::move(t));
	}

	auto makeSegment(const modeler_t& m, const Pnt2d& pt, const Standard_Real ang, const Standard_Real len)
	{
		auto t = tools::MakeSegment(pt, ang, len);
		return m->Import(std::move(t));
	}

	auto makeCircArc(const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto t = tools::MakeCircArc(p0, p1, p2);
		return m->Import(std::move(t));
	}

	auto makeCircArc(const modeler_t& m, const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p1)
	{
		auto t = tools::MakeCircArc(p0, v0, p1);
		return m->Import(std::move(t));
	}

	auto makeCircArc(const modeler_t& m, const gp_Circ2d& c, const Standard_Real ang0, const Standard_Real ang1)
	{
		auto t = tools::MakeCircArc(c, ang0, ang1);
		return m->Import(std::move(t));
	}

	auto makeCircArc(const modeler_t& m, const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto t = tools::MakeCircArc(c, p0, p1);
		return m->Import(std::move(t));
	}

	auto makeElipsArc(const modeler_t& m, const gp_Elips2d& e, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto t = tools::MakeElipsArc(e, p0, p1);
		return m->Import(std::move(t));
	}

	auto makeElipsArc(const modeler_t& m, const gp_Elips2d& e, const Standard_Real ang0, const Standard_Real ang1)
	{
		auto t = tools::MakeElipsArc(e, ang0, ang1);
		return m->Import(std::move(t));
	}

	auto makeHyprArc(const modeler_t& m, const gp_Hypr2d& h, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto t = tools::MakeHyprArc(h, p0, p1);
		return m->Import(std::move(t));
	}

	auto makeHyprArc(const modeler_t& m, const gp_Hypr2d& h, const Standard_Real ang0, const Standard_Real ang1)
	{
		auto t = tools::MakeHyprArc(h, ang0, ang1);
		return m->Import(std::move(t));
	}

	auto makeCircle(const modeler_t& m, const gp_Circ2d& c)
	{
		auto t = tools::MakeCircle(c);
		return m->Import(std::move(t));
	}

	auto makeCircle(const modeler_t& m, const gp_Circ2d& c, const Pnt2d& pt)
	{
		auto t = tools::MakeCircle(c, pt);
		return m->Import(std::move(t));
	}

	auto makeCircle(const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto t = tools::MakeCircle(p0, p1, p2);
		return m->Import(std::move(t));
	}

	auto makeCircle(const modeler_t& m, const Pnt2d& pt, const Standard_Real r)
	{
		auto t = tools::MakeCircle(pt, r);
		return m->Import(std::move(t));
	}

	auto makeCircle(const modeler_t& m, const Pnt2d& c, const Pnt2d& pt)
	{
		auto t = tools::MakeCircle(c, pt);
		return m->Import(std::move(t));
	}

	auto makeEllipse(const modeler_t& m, const gp_Elips2d& e)
	{
		auto t = tools::MakeEllipse(e);
		return m->Import(std::move(t));
	}

	auto makeEllipse(const modeler_t& m, const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)
	{
		auto t = tools::MakeEllipse(s0, s1, c);
		return m->Import(std::move(t));
	}

	void makeRectangular(const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto t = tools::MakeRectangular(p0, p1);
		m->Import(std::move(t));
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

	auto makePlane(const modeler_t& m, selList& l)
	{
		return m->MakePlane(l);
	}

	auto makePlane(const modeler_t& m)
	{
		return makePlane(m, selt);
	}

	void makePlanes(const modeler_t& m)
	{
		m->MakePlanes(selt);
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

	void addNewTypes(const module_t& mod)
	{
		mod->add(chaiscript::fun([]() {auto t = makeTransform(); return std::move(t); }), "createTransform");
		mod->add(chaiscript::fun([](const Standard_Real x, const Standard_Real y) {auto t = makePoint(x, y); return std::move(t); }), "createPoint");
		mod->add(chaiscript::fun([](const Standard_Real x, const Standard_Real y) {auto t = makeDirection(x, y); return std::move(t); }), "createDirection");
		mod->add(chaiscript::fun([](const Pnt2d& pt, const Dir2d& d) {auto t = makeAxis(pt, d); return std::move(t); }), "createAxis");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const Standard_Real r) {auto t = makeGeoCirc(ax, r); return std::move(t); }), "createGeoCirc");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const Standard_Real majR, const Standard_Real minR) {auto t = makeGeoElips(ax, majR, minR); return std::move(t); }), "createGeoElips");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const Standard_Real majR, const Standard_Real minR) {auto t = makeGeoHypr(ax, majR, minR); return std::move(t); }), "createGeoHypr");
		mod->add(chaiscript::fun([](const gp_Ax2d& ax, const Standard_Real focal) {auto t = makeGeoParab(ax, focal); return std::move(t); }), "createGeoParab");

		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1)-> Standard_Integer {return makeSegment(m, p0, p1); }), "createSegment");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Standard_Real ang, const Standard_Real len)-> Standard_Integer {return makeSegment(m, p0, ang, len); }), "createSegment");

		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> Standard_Integer {return makeCircArc(m, p0, p1, p2); }), "createCircArc");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Vec2d& v, const Pnt2d& p2)-> Standard_Integer {return makeCircArc(m, p0, v, p2); }), "createCircArc");
		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Circ2d& c, const Standard_Real ang0, const Standard_Real ang1)-> Standard_Integer {return makeCircArc(m, c, ang0, ang1); }), "createCircArc");
		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)-> Standard_Integer {return makeCircArc(m, c, p0, p1); }), "createCircArc");

		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Elips2d& el, const Pnt2d& p0, const Pnt2d& p1)-> Standard_Integer {return makeElipsArc(m, el, p0, p1); }), "creatElipsArc");
		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Elips2d& el, const Standard_Real ang0, const Standard_Real ang1)-> Standard_Integer {return makeElipsArc(m, el, ang0, ang1); }), "creatElipsArc");

		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Hypr2d& hr, const Pnt2d& p0, const Pnt2d& p1)-> Standard_Integer {return makeHyprArc(m, hr, p0, p1);}), "createHyprArc");
		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Hypr2d& hr, const Standard_Real ang0, const Standard_Real ang1)-> Standard_Integer {return makeHyprArc(m, hr, ang0, ang1);}), "createHyprArc");

		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Circ2d& c)-> Standard_Integer {return makeCircle(m, c); }), "createCirc");
		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Circ2d& c, const Pnt2d& p)-> Standard_Integer {return makeCircle(m, c, p); }), "createCirc");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> Standard_Integer {return makeCircle(m, p0, p1, p2); }), "createCirc");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Standard_Real r)-> Standard_Integer {return makeCircle(m, p0, r); }), "createCirc");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& c, const Pnt2d& p)-> Standard_Integer {return makeCircle(m, c, p); }), "createCirc");

		mod->add(chaiscript::fun([](const modeler_t& m, const gp_Elips2d& el)-> Standard_Integer {return makeEllipse(m, el); }), "createElips");
		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)-> Standard_Integer {return makeEllipse(m, s0, s1, c);}), "createElips");

		mod->add(chaiscript::fun([](const modeler_t& m, const Pnt2d& p0, const Pnt2d& p1)-> void {makeRectangular(m, p0, p1); }), "createRectangular");
	}

	void setOps(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const modeler_t& m, const int id)-> edge_t {auto t = selectEdge(m, id); return std::move(t); }), "selectEdge");
		mod->add(chaiscript::fun([](const modeler_t& m, const edge_t& e)-> void {removeEdge(m, e); }), "removeEdge");
		mod->add(chaiscript::fun([](const modeler_t& m, const int id)-> void {selectList(m, id); }), "addToSelectList");
		mod->add(chaiscript::fun([](const modeler_t& m, const edge_t& e)-> void {deSelectFromList(m, e); }), "removeFromSelectList");
		mod->add(chaiscript::fun([](const modeler_t& m)-> void {selectAllList(m); }), "selectAll");
		mod->add(chaiscript::fun([](const modeler_t& m)-> void {deSelectAllList(m); }), "deSelectAll");
		mod->add(chaiscript::fun([](const modeler_t& m)-> int {return makePlane(m); }), "createPlane");
	}

	void setBooleans(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {unionOp(m, pl0, pl1); }), "union");
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {subtOp(m, pl0, pl1); }), "subtract");
		mod->add(chaiscript::fun([](const modeler_t& m, const int pl0, const int pl1)-> void {intrsctOp(m, pl0, pl1); }), "intersection");
	}
}

int main()
{
	return 0;
}
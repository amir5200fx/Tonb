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

	static const auto modeler = std::make_shared<Cad2d_Modeler>();
	static selList selt;

	

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

	auto makeCircArc(const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(p0, v0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const gp_Circ2d& circ, const double angl0, const double angl1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(circ, angl0, angl1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircArc(const gp_Circ2d& circ, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircArc(circ, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeElipsArc(const gp_Elips2d& elips, const double angl0, const double angl1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeElipsArc(elips, angl0, angl1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeElipsArc(const gp_Elips2d& elips, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeElipsArc(elips, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeHyperArc(const gp_Hypr2d& hyper, const double angl0, const double angl1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeHyprArc(hyper, angl0, angl1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeHyperArc(const gp_Hypr2d& hyper, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeHyprArc(hyper, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeParabArc(const gp_Parab2d& parab, const double angl0, const double angl1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeParbArc(parab, angl0, angl1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeParabArc(const gp_Parab2d& parab, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto item = cad2dLib::Modeler_Tools::MakeParabArc(parab, p0, p1);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const gp_Circ2d& circ)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(circ);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const gp_Circ2d& circle, const Pnt2d& pt)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(circle, pt);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(p0, p1, p2);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& c, const double r)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(c, r);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeCircle(const Pnt2d& c, const Pnt2d& pt)
	{
		auto item = cad2dLib::Modeler_Tools::MakeCircle(c, pt);
		auto t = getModeler()->SelectEdge(getModeler()->Import(std::move(item)));
		return std::move(t);
	}

	auto makeEllipse(const gp_Elips2d& elips)
	{
		auto item = cad2dLib::Modeler_Tools::MakeEllipse(elips);
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


	static const auto chai = std::make_shared<chaiscript::ChaiScript>();

	static const auto& getChai()
	{
		return chai;
	}

	class InputGeometricFunctions
	{
	public:

		InputGeometricFunctions()
		{
			auto mod = std::make_shared<chaiscript::Module>();

			mod->add(chaiscript::fun([](const double x, const double y)-> auto {return makePoint(x, y); }), "MakePnt");
			/*mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& v)-> auto {return makeGeoAx2d(p, v); }), "MakeAxis");
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
			mod->add(chaiscript::fun([](const gp_Ax2d& directrix, const gp_Pnt2d& focus, const bool s)-> auto {return makeGeoParab(directrix, focus, s); }), "makeGeoParab");*/

			getChai()->add(mod);

		}

	};

	static const InputGeometricFunctions inputGeometricFunctions;


}

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
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeSegment(p0, p1); }), "createSegment");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const double ang, const double len)-> auto {return makeSegment(p0, ang, len); }), "createSegment");

		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircArc(p0, p1, p2); }), "createCircArc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Vec2d& v, const Pnt2d& p2)-> auto {return makeCircArc(p0, v, p2); }), "createCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const double ang0, const double ang1)-> auto {return makeCircArc(c, ang0, ang1); }), "createCircArc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeCircArc(c, p0, p1); }), "createCircArc");

		mod->add(chaiscript::fun([](const gp_Elips2d& el, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeElipsArc(el, p0, p1); }), "creatElipsArc");
		mod->add(chaiscript::fun([](const gp_Elips2d& el, const double ang0, const Standard_Real ang1)-> auto {return makeElipsArc(el, ang0, ang1); }), "creatElipsArc");

		mod->add(chaiscript::fun([](const gp_Hypr2d& hr, const Pnt2d& p0, const Pnt2d& p1)-> auto {return makeHyperArc(hr, p0, p1);}), "createHyprArc");
		mod->add(chaiscript::fun([](const gp_Hypr2d& hr, const double ang0, const double ang1)-> auto {return makeHyperArc(hr, ang0, ang1);}), "createHyprArc");

		mod->add(chaiscript::fun([](const gp_Circ2d& c)-> auto {return makeCircle(c); }), "createCirc");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p)-> auto {return makeCircle(c, p); }), "createCirc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> auto {return makeCircle(p0, p1, p2); }), "createCirc");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const double r)-> auto {return makeCircle(p0, r); }), "createCirc");
		mod->add(chaiscript::fun([](const Pnt2d& c, const Pnt2d& p)-> auto {return makeCircle(c, p); }), "createCirc");

		mod->add(chaiscript::fun([](const gp_Elips2d& el)-> auto {return makeEllipse(el); }), "createElips");
		mod->add(chaiscript::fun([](const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)-> auto {return makeEllipse(s0, s1, c);}), "createElips");

		//mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeRectangular(p0, p1); }), "createRectangular");
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

	void setGeoFuncs(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const double x, const double y)-> auto {return makePoint(x, y); }), "MakePnt");
		/*mod->add(chaiscript::fun([](const Pnt2d& p, const Dir2d& v)-> auto {return makeGeoAx2d(p, v); }), "MakeAxis");
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
		mod->add(chaiscript::fun([](const gp_Ax2d& directrix, const gp_Pnt2d& focus, const bool s)-> auto {return makeGeoParab(directrix, focus, s); }), "makeGeoParab");*/
	}


	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const Pnt2d& p)-> void {print(p); }), "print");
	}
}

using namespace tnbLib;

int main()
{

	chaiscript::ChaiScript chai;

	auto mod = std::make_shared<chaiscript::Module>();

	setGeoFuncs(mod);

	setGlobals(mod);

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

	
	
	return 0;
}
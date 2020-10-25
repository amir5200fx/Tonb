#include <Geo_Scripts.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#include <TopoDS_Shape.hxx>
#include <gp_Ax2.hxx>
#include <Precision.hxx>

Standard_Real 
tnbLib::script::Geo::getConfusion() const
{
	return Precision::Confusion();
}

tnbLib::Pnt3d 
tnbLib::script::Geo::createPnt3d() const
{
	Pnt3d pt;
	return std::move(pt);
}

tnbLib::Pnt3d 
tnbLib::script::Geo::createPnt3d
(
	const Standard_Real x, 
	const Standard_Real y,
	const Standard_Real z
) const
{
	Pnt3d pt(x, y, z);
	return std::move(pt);
}

tnbLib::Pnt2d 
tnbLib::script::Geo::createPnt2d() const
{
	Pnt2d pt;
	return std::move(pt);
}

tnbLib::Pnt2d 
tnbLib::script::Geo::createPnt2d
(
	const Standard_Real x, 
	const Standard_Real y
) const
{
	Pnt2d pt(x, y);
	return std::move(pt);
}

tnbLib::Dir2d 
tnbLib::script::Geo::createDir2d() const
{
	Dir2d d;
	return std::move(d);
}

tnbLib::Dir2d 
tnbLib::script::Geo::createDir2d
(
	const Standard_Real x, 
	const Standard_Real y
) const
{
	Dir2d d(x, y);
	return std::move(d);
}

tnbLib::Dir3d 
tnbLib::script::Geo::createDir3d() const
{
	Dir3d d;
	return std::move(d);
}

tnbLib::Dir3d 
tnbLib::script::Geo::createDir3d
(
	const Standard_Real x,
	const Standard_Real y, 
	const Standard_Real z
) const
{
	Dir3d d(x, y, z);
	return std::move(d);
}

gp_Ax1 
tnbLib::script::Geo::create_gpAx1() const
{
	return gp_Ax1();
}

gp_Ax1 
tnbLib::script::Geo::create_gpAx1
(
	const Pnt3d & p,
	const Dir3d & d
) const
{
	gp_Ax1 ax(p, d);
	return std::move(ax);
}

tnbLib::Entity2d_Box 
tnbLib::script::Geo::createBox2d
(
	const Pnt2d & p0, 
	const Pnt2d & p1
) const
{
	Entity2d_Box b(p0, p1);
	return std::move(b);
}

tnbLib::Entity3d_Box 
tnbLib::script::Geo::createBox3d
(
	const Pnt3d & p0,
	const Pnt3d & p1
) const
{
	Entity3d_Box b(p0, p1);
	return std::move(b);
}

std::shared_ptr<tnbLib::Geo_UniDistb> 
tnbLib::script::Geo::newUniformDistb
(
	const Standard_Real x0,
	const Standard_Real x1,
	const Standard_Integer n
) const
{
	auto d = std::make_shared<Geo_UniDistb>(n);
	d->SetLower(x0);
	d->SetUpper(x1);
	return std::move(d);
}

std::shared_ptr<tnbLib::Geo_CosineDistb> 
tnbLib::script::Geo::newCosineDistb
(
	const Standard_Real x0,
	const Standard_Real x1, 
	const Standard_Integer n
) const
{
	auto d = std::make_shared<Geo_CosineDistb>(n);
	d->SetLower(x0);
	d->SetUpper(x1);
	return std::move(d);
}

namespace tnbLib
{

	static Standard_Real geo_get_confusion()
	{
		return Precision::Confusion();
	}

	/*static std::shared_ptr<Geo_UniDistb> geo_get_uniform_distb(const Standard_Integer n, const TopoDS_Shape& s)
	{

	}*/
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::script::load_geo(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::user_type<Geo>(), "GeoModule");
	mod->add(chaiscript::fun([]() {return std::make_shared<Geo>(); }), "newGeoModule");

	typedef std::shared_ptr<Geo> geo_t;

	mod->add(chaiscript::fun([](const geo_t& t)-> Standard_Real {Debug_Null_Pointer(t); return t->getConfusion(); }), "getPrecision");

	mod->add(chaiscript::fun([](const geo_t& t)-> Pnt3d {auto p = t->createPnt3d(); return std::move(p); }), "createPnt3d");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x, const Standard_Real y, const Standard_Real z)-> Pnt3d {auto p = t->createPnt3d(x, y, z); return std::move(p); }), "createPnt3d");
	mod->add(chaiscript::fun([](const geo_t& t)-> Pnt2d {auto p = t->createPnt2d(); return std::move(p); }), "createPnt2d");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x, const Standard_Real y)-> Pnt2d {auto p = t->createPnt2d(x, y); return std::move(p); }), "createPnt2d");

	mod->add(chaiscript::fun([](const geo_t& t)-> Dir2d {return t->createDir2d(); }), "createDir2d");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x, const Standard_Real y)-> Dir2d {return t->createDir2d(x, y); }), "createDir2d");
	mod->add(chaiscript::fun([](const geo_t& t)-> Dir3d {return t->createDir3d(); }), "createDir3d");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x, const Standard_Real y, const Standard_Real z)-> Dir3d {return t->createDir3d(x, y, z); }), "createDir3d");

	mod->add(chaiscript::fun([](const geo_t& t)-> gp_Ax1 {return t->create_gpAx1(); }), "create_gpAx1");
	mod->add(chaiscript::fun([](const geo_t& t, const Pnt3d& p, const Dir3d& d)-> gp_Ax1 {return t->create_gpAx1(p, d); }), "create_gpAx1");

	mod->add(chaiscript::fun([](const geo_t& t, const Pnt2d& p1, const Pnt2d& p2)-> Entity2d_Box {auto b = t->createBox2d(p1, p2); return std::move(b); }), "createBox2d");
	mod->add(chaiscript::fun([](const geo_t& t, const Pnt3d& p1, const Pnt3d& p2)-> Entity3d_Box {auto b = t->createBox3d(p1, p2); return std::move(b); }), "createBox3d");

	mod->add(chaiscript::user_type<Pnt3d>(), "gPnt3d");
	mod->add(chaiscript::constructor<Pnt3d(const Standard_Real, const Standard_Real, const Standard_Real)>(), "gPnt3d");

	mod->add(chaiscript::user_type<Dir3d>(), "gDir3d");
	mod->add(chaiscript::constructor<Dir3d(const Standard_Real, const Standard_Real, const Standard_Real)>(), "gDir3d");

	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.X(); }), "getX");
	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.Y(); }), "getY");
	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.Z(); }), "getZ");

	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetX(x); }), "setX");
	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetY(x); }), "setY");
	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetZ(x); }), "setZ");

	mod->add(chaiscript::fun([](const Dir3d& p) {return p.X(); }), "getX");
	mod->add(chaiscript::fun([](const Dir3d& p) {return p.Y(); }), "getY");
	mod->add(chaiscript::fun([](const Dir3d& p) {return p.Z(); }), "getZ");

	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetX(x); }), "setX");
	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetY(x); }), "setY");
	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetZ(x); }), "setZ");

	mod->add(chaiscript::user_type<gp_Ax1>(), "gpAx1");
	mod->add(chaiscript::constructor<gp_Ax1(const Pnt3d&, const Dir3d&)>(), "gpAx1");
	mod->add(chaiscript::fun([](gp_Ax1& ax, const Dir3d& d) {ax.SetDirection(d); }), "setDirection");
	mod->add(chaiscript::fun([](gp_Ax1& ax, const Pnt3d& d) {ax.SetLocation(d); }), "setLocation");
	mod->add(chaiscript::fun([](const gp_Ax1& ax) {return ax.Direction(); }), "getDirection");
	mod->add(chaiscript::fun([](const gp_Ax1& ax) {return ax.Location(); }), "getLocation");
	mod->add(chaiscript::fun([](const gp_Ax1& ax0, const gp_Ax1& ax1) {return ax0.Angle(ax1); }), "angle");

	mod->add(chaiscript::user_type<gp_Ax2>(), "gpAx2");
	mod->add(chaiscript::constructor<gp_Ax2(const Pnt3d&, const Dir3d&, const Dir3d&)>(), "gpAx2");
	mod->add(chaiscript::constructor<gp_Ax2(const Pnt3d&, const Dir3d&)>(), "gpAx2");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Pnt3d& p) {ax.SetLocation(p); }), "setLocation");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetDirection(d); }), "setDirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.Location(); }), "getLocation");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.Direction(); }), "getDirection");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetXDirection(d); }), "set_xDirection");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetYDirection(d); }), "set_yDirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.XDirection(); }), "get_xDirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.YDirection(); }), "get_yDirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax0, const gp_Ax2& ax1, const Standard_Real t0, const Standard_Real t1) {return ax0.IsCoplanar(ax1, t0, t1); }), "isCoplanar");
	mod->add(chaiscript::fun([](const gp_Ax2& ax0, const gp_Ax2& ax1) {return ax0.Angle(ax1); }), "angle");

	mod->add(chaiscript::user_type<Entity3d_Box>(), "gBox3d");
	mod->add(chaiscript::constructor<Entity3d_Box(const Pnt3d&, const Pnt3d&)>(), "gBox3d");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.P0(); }), "getP0");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.P1(); }), "getP1");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.Diameter(); }), "getDiameter");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.CalcCentre(); }), "getCentre");

	mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1) {auto s = std::make_shared<Entity3d_Box>(p0, p1); return std::move(s); }), "new_gBox3d");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> const Pnt3d& {return t->P0(); }), "getP0");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> const Pnt3d& {return t->P1(); }), "getP1");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> Standard_Real {return t->Diameter(); }), "getDiameter");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> Pnt3d {return t->CalcCentre(); }), "getCentre");

	typedef std::shared_ptr<Geo_UniDistb> gUniDistb_t;
	typedef std::shared_ptr<Geo_CosineDistb> gCosineDistb_t;

	mod->add(chaiscript::user_type<gUniDistb_t>(), "gUniDistb");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x0, const Standard_Real x1, const Standard_Integer n)->gUniDistb_t {auto d = t->newUniformDistb(x0, x1, n); return std::move(d); }), "newUniDistb");
	mod->add(chaiscript::fun([](const geo_t& t, const Standard_Real x0, const Standard_Real x1, const Standard_Integer n)->gCosineDistb_t {auto d = t->newCosineDistb(x0, x1, n); return std::move(d); }), "newCosineDistb");

	typedef std::shared_ptr<Entity2d_Polygon> poly2d_t;
	typedef std::shared_ptr<Entity3d_Polygon> poly3d_t;

	mod->add(chaiscript::user_type<poly2d_t>(), "gPolygon2d");
	mod->add(chaiscript::user_type<poly3d_t>(), "gPolygon3d");

	mod->add(chaiscript::fun([](const poly2d_t& p, OFstream& f)-> void {Debug_Null_Pointer(p); p->ExportToPlt(f); }), "exportToPlt");
	//mod->add(chaiscript::fun([](const poly2d_t& p, std::fstream& f)-> void {Debug_Null_Pointer(p); p->ExportToPlt(f); }), "exportToPlt");

	mod->add(chaiscript::fun([](const poly3d_t& p, OFstream& f)-> void {Debug_Null_Pointer(p); p->ExportToPlt(f); }), "exportToPlt");
	//mod->add(chaiscript::fun([](const poly3d_t& p, std::fstream& f)-> void {Debug_Null_Pointer(p); p->ExportToPlt(f); }), "exportToPlt");

	chai.add(mod);
}
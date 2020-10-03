#include <Geo_Scripts.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#include <TopoDS_Shape.hxx>
#include <gp_Ax2.hxx>
#include <Precision.hxx>

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

	mod->add(chaiscript::fun(&geo_get_confusion), "get_confusion");

	mod->add(chaiscript::user_type<Pnt3d>(), "geo_pnt3d");
	mod->add(chaiscript::constructor<Pnt3d(const Standard_Real, const Standard_Real, const Standard_Real)>(), "geo_pnt3d");

	mod->add(chaiscript::user_type<Dir3d>(), "geo_dir3d");
	mod->add(chaiscript::constructor<Dir3d(const Standard_Real, const Standard_Real, const Standard_Real)>(), "geo_dir3d");

	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.X(); }), "get_x");
	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.Y(); }), "get_y");
	mod->add(chaiscript::fun([](const Pnt3d& p) {return p.Z(); }), "get_z");

	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetX(x); }), "set_x");
	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetY(x); }), "set_y");
	mod->add(chaiscript::fun([](Pnt3d& p, const Standard_Real x) { p.SetZ(x); }), "set_z");

	mod->add(chaiscript::fun([](const Dir3d& p) {return p.X(); }), "get_x");
	mod->add(chaiscript::fun([](const Dir3d& p) {return p.Y(); }), "get_y");
	mod->add(chaiscript::fun([](const Dir3d& p) {return p.Z(); }), "get_z");

	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetX(x); }), "set_x");
	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetY(x); }), "set_y");
	mod->add(chaiscript::fun([](Dir3d& p, const Standard_Real x) { p.SetZ(x); }), "set_z");

	mod->add(chaiscript::user_type<gp_Ax1>(), "gp_ax1");
	mod->add(chaiscript::constructor<gp_Ax1(const Pnt3d&, const Dir3d&)>(), "gp_ax1");
	mod->add(chaiscript::fun([](gp_Ax1& ax, const Dir3d& d) {ax.SetDirection(d); }), "set_direction");
	mod->add(chaiscript::fun([](gp_Ax1& ax, const Pnt3d& d) {ax.SetLocation(d); }), "set_location");
	mod->add(chaiscript::fun([](const gp_Ax1& ax) {return ax.Direction(); }), "get_direction");
	mod->add(chaiscript::fun([](const gp_Ax1& ax) {return ax.Location(); }), "get_location");
	mod->add(chaiscript::fun([](const gp_Ax1& ax0, const gp_Ax1& ax1) {return ax0.Angle(ax1); }), "angle");

	mod->add(chaiscript::user_type<gp_Ax2>(), "gp_ax2");
	mod->add(chaiscript::constructor<gp_Ax2(const Pnt3d&, const Dir3d&, const Dir3d&)>(), "gp_ax2");
	mod->add(chaiscript::constructor<gp_Ax2(const Pnt3d&, const Dir3d&)>(), "gp_ax2");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Pnt3d& p) {ax.SetLocation(p); }), "set_location");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetDirection(d); }), "set_direction");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.Location(); }), "get_location");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.Direction(); }), "get_direction");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetXDirection(d); }), "set_xdirection");
	mod->add(chaiscript::fun([](gp_Ax2& ax, const Dir3d& d) {ax.SetYDirection(d); }), "set_ydirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.XDirection(); }), "get_xdirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax) {return ax.YDirection(); }), "get_ydirection");
	mod->add(chaiscript::fun([](const gp_Ax2& ax0, const gp_Ax2& ax1, const Standard_Real t0, const Standard_Real t1) {return ax0.IsCoplanar(ax1, t0, t1); }), "is_coplanar");
	mod->add(chaiscript::fun([](const gp_Ax2& ax0, const gp_Ax2& ax1) {return ax0.Angle(ax1); }), "angle");

	mod->add(chaiscript::user_type<Entity3d_Box>(), "geo_box3d");
	mod->add(chaiscript::constructor<Entity3d_Box(const Pnt3d&, const Pnt3d&)>(), "geo_box3d");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.P0(); }), "get_p0");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.P1(); }), "get_p1");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.Diameter(); }), "get_diameter");
	mod->add(chaiscript::fun([](const Entity3d_Box& b) {return b.CalcCentre(); }), "get_centre");

	mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1) {auto s = std::make_shared<Entity3d_Box>(p0, p1); return std::move(s); }), "geo_new_box3d");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> const Pnt3d& {return t->P0(); }), "get_p0");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> const Pnt3d& {return t->P1(); }), "get_p1");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> Standard_Real {return t->Diameter(); }), "get_diameter");
	mod->add(chaiscript::fun([](const std::shared_ptr<Entity3d_Box>& t)-> Pnt3d {return t->CalcCentre(); }), "get_centre");

	mod->add(chaiscript::user_type<Geo_UniDistb>(), "geo_uniform_distb");
	mod->add(chaiscript::fun([](const Standard_Real x0, const Standard_Real x1, const Standard_Integer n) {auto d = std::make_shared<Geo_UniDistb>(n); d->SetLower(x0); d->SetUpper(x1); d->Perform(); }), "geo_uniform_distb");

	mod->add(chaiscript::user_type<Geo_CosineDistb>(), "geo_cosine_distb");
	mod->add(chaiscript::fun([](const Standard_Real x0, const Standard_Real x1, const Standard_Integer n) {auto d = std::make_shared<Geo_CosineDistb>(n); d->SetLower(x0); d->SetUpper(x1); d->Perform(); }), "geo_cosine_distb");

	chai.add(mod);
}
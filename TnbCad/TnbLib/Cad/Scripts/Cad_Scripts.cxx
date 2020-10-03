#include <Cad_Scripts.hxx>

#include <Entity3d_Box.hxx>
#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <messageStream.hxx>

#include <TopoDS_Shape.hxx>
#include <Bnd_Box.hxx>
#include <gp_Ax2.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>



void tnbLib::script::load_cad(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::fun([](const TopoDS_Shape& t) {return Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(t)).Diameter(); }), "cad_get_diameter");

	mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1) {auto s = Cad_ShapeTools::Box(p0, p1); return std::move(s); }), "cad_create_box");
	mod->add(chaiscript::fun([](const gp_Ax2& ax, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz) {auto s = Cad_ShapeTools::Box(ax, dx, dy, dz); return std::move(s); }), "cad_create_box");
	mod->add(chaiscript::fun([](const gp_Ax2& ax, const Standard_Real r, const Standard_Real h) {auto s = Cad_ShapeTools::Cylinder(ax, r, h); return std::move(s); }), "cad_create_cylinder");
	mod->add(chaiscript::fun([](const gp_Ax2& ax, const Standard_Real r) {auto s = Cad_ShapeTools::Sphere(ax, r); return std::move(s); }), "cad_create_sphere");
	mod->add(chaiscript::fun([](const Pnt3d& c, const Standard_Real r) {auto s = Cad_ShapeTools::Sphere(c, r); return std::move(s); }), "cad_create_sphere");

	chai.add(mod);
}
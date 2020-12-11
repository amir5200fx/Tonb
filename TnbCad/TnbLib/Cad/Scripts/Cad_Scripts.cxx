//#include <Cad_Scripts.hxx>
//
//#include <Entity3d_Box.hxx>
//#include <Cad_Tools.hxx>
//#include <Cad_ShapeTools.hxx>
//#include <TnbError.hxx>
//#include <OSstream.hxx>
//#include <messageStream.hxx>
//
//#include <TopoDS_Shape.hxx>
//#include <Bnd_Box.hxx>
//#include <gp_Ax2.hxx>
//
//Standard_Real 
//tnbLib::script::Cad::getDiameter(const TopoDS_Shape &s)
//{
//	Debug_If_Condition(s.IsNull());
//	auto b = getBoundingBox(s);
//	return b.Diameter();
//}
//
//tnbLib::Entity3d_Box
//tnbLib::script::Cad::getBoundingBox(const TopoDS_Shape & s)
//{
//	auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(s));
//	return std::move(b);
//}
//
//TopoDS_Shape 
//tnbLib::script::Cad::newBox
//(
//	const Pnt3d & p0,
//	const Pnt3d & p1
//)
//{
//	auto s = Cad_ShapeTools::Box(p0, p1);
//	return std::move(s);
//}
//
//TopoDS_Shape 
//tnbLib::script::Cad::newBox
//(
//	const gp_Ax2 & ax,
//	const Standard_Real dx,
//	const Standard_Real dy,
//	const Standard_Real dz
//)
//{
//	auto s = Cad_ShapeTools::Box(ax, dx, dy, dz); 
//	return std::move(s);
//}
//
//TopoDS_Shape 
//tnbLib::script::Cad::newCylinder
//(
//	const gp_Ax2 & ax,
//	const Standard_Real r,
//	const Standard_Real h
//)
//{
//	auto s = Cad_ShapeTools::Cylinder(ax, r, h); 
//	return std::move(s);
//}
//
//TopoDS_Shape 
//tnbLib::script::Cad::newSphere
//(
//	const gp_Ax2 & ax,
//	const Standard_Real r
//)
//{
//	auto s = Cad_ShapeTools::Sphere(ax, r); 
//	return std::move(s);
//}
//
//TopoDS_Shape 
//tnbLib::script::Cad::newSphere
//(
//	const Pnt3d & c, 
//	const Standard_Real r
//)
//{
//	auto s = Cad_ShapeTools::Sphere(c, r); 
//	return std::move(s);
//}
//
//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo
//
//#include <chaiscript/chaiscript.hpp>
//
//
//
//void tnbLib::script::load_cad(chaiscript::ChaiScript& chai)
//{
//	auto mod = std::make_shared<chaiscript::Module>();
//
//	typedef std::shared_ptr<Cad> cad_t;
//
//	mod->add(chaiscript::user_type<cad_t>(), "CadModule");
//	mod->add(chaiscript::fun([]() {auto t = std::make_shared<Cad>(); return std::move(t); }), "newCadModule");
//
//	mod->add(chaiscript::fun([](const cad_t& t, const Pnt3d& p0, const Pnt3d& p1)-> TopoDS_Shape {Debug_Null_Pointer(t); return t->newBox(p0, p1); }), "newBox");
//	mod->add(chaiscript::fun([](const cad_t& t, const gp_Ax2& ax, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz)-> TopoDS_Shape {Debug_Null_Pointer(t); return t->newBox(ax, dx, dy, dz); }), "newBox");
//	mod->add(chaiscript::fun([](const cad_t& t, const gp_Ax2& ax, const Standard_Real r, const Standard_Real h)-> TopoDS_Shape {Debug_Null_Pointer(t); return t->newCylinder(ax, r, h); }), "newCylinder");
//	mod->add(chaiscript::fun([](const cad_t& t, const gp_Ax2& ax, const Standard_Real r)-> TopoDS_Shape {Debug_Null_Pointer(t); return t->newSphere(ax, r); }), "newSphere");
//	mod->add(chaiscript::fun([](const cad_t& t, const Pnt3d& c, const Standard_Real r)->TopoDS_Shape {Debug_Null_Pointer(t); return t->newSphere(c, r); }), "newSphere");
//
//	mod->add(chaiscript::fun([](const cad_t& t, const TopoDS_Shape& s)-> Standard_Real {Debug_Null_Pointer(t); return t->getDiameter(s); }), "getDiameter");
//	mod->add(chaiscript::fun([](const cad_t& t, const TopoDS_Shape& s)-> Entity3d_Box {Debug_Null_Pointer(t); auto b = t->getBoundingBox(s); return std::move(b); }), "getBoundingBox");
//
//	chai.add(mod);
//}
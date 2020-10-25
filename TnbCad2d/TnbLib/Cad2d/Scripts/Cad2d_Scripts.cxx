#include <Cad2d_Scripts.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::script::Cad2d::uniformDiscretize
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Integer nSeg
) const
{
	auto n = std::max(1, nSeg);
	auto poly = Pln_Tools::UniformDiscrete(theCurve, n);
	return std::move(poly);
}

void tnbLib::script::Cad2d::exportToPlt
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Integer n,
	OFstream & f
)
{
	auto poly = uniformDiscretize(theCurve, n);
	poly->ExportToPlt(f);
}

void tnbLib::script::Cad2d::exportToPlt
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Integer n,
	const word & name
)
{
	fileName myFileName(name);
	OFstream file(myFileName);

	exportToPlt(theCurve, n, file);
}

void tnbLib::script::Cad2d::exportToPlt
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Integer n, 
	const std::string & name
)
{
	fileName myFileName(name);
	OFstream file(myFileName);

	exportToPlt(theCurve, n, file);
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::script::load_cad2d(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	typedef std::shared_ptr<Cad2d> cad_t;

	mod->add(chaiscript::user_type<cad_t>(), "Cad2dModule");
	mod->add(chaiscript::fun([]() {auto t = std::make_shared<Cad2d>(); return std::move(t); }), "newCad2dModule");

	mod->add(chaiscript::fun([](const cad_t& t, const Handle(Geom2d_Curve)& c, const Standard_Integer n)->std::shared_ptr<Entity2d_Polygon> {Debug_Null_Pointer(t); auto p = t->uniformDiscretize(c, n); return std::move(p); }), "uniformDiscrete");
	mod->add(chaiscript::fun([](const cad_t& t, const Handle(Geom2d_Curve)& c, const Standard_Integer n, OFstream& f)-> void {Debug_Null_Pointer(t); t->exportToPlt(c, n, f); }), "exportToPlt");
	mod->add(chaiscript::fun([](const cad_t& t, const Handle(Geom2d_Curve)& c, const Standard_Integer n, const word& f)-> void {Debug_Null_Pointer(t); t->exportToPlt(c, n, f); }), "exportToPlt");
	mod->add(chaiscript::fun([](const cad_t& t, const Handle(Geom2d_Curve)& c, const Standard_Integer n, const std::string& f)-> void {Debug_Null_Pointer(t); t->exportToPlt(c, n, f); }), "exportToPlt");

	chai.add(mod);
}
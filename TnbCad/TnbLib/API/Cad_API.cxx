#include <Cad_API.hxx>

#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const Pnt3d& p0, const Pnt3d& p1)
{
	auto shape = make_box(p0, p1, "box");
	return { std::move(shape) };
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const Pnt3d& p0, const Pnt3d& p1, const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, p1));
	shape->SetIndex(0);
	shape->SetName(name);
	return { std::move(shape) };
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const Pnt3d& p0, double dx, double dy, double dz)
{
	auto shape = make_box(p0, dx, dy, dz, "box");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const Pnt3d& p0, double dx, double dy, double dz,
	const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, dx, dy, dz));
	shape->SetIndex(0);
	shape->SetName("box");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const gp_Ax2& ax, double dx, double dy, double dz)
{
	auto shape = make_box(ax, dx, dy, dz, "box");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_box(const gp_Ax2& ax, double dx, double dy, double dz,
	const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(ax, dx, dy, dz));
	shape->SetIndex(0);
	shape->SetName("box");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_cylinder(const gp_Ax2& ax, double r, double h)
{
	auto shape = make_cylinder(ax, r, h, "cylinder");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_cylinder(const gp_Ax2& ax, double r, double h,
	const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_cylinder(const gp_Ax2& ax, double r, double h, double angle)
{
	auto shape = make_cylinder(ax, r, h, angle, "cylinder");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_cylinder(const gp_Ax2& ax, double r, double h, double angle,
	const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h, angle));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const Pnt3d& c, double r)
{
	auto shape = make_sphere(c, r, "sphere");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const Pnt3d& c, double r, const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(c, r));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r)
{
	auto shape = make_sphere(ax, r, "sphere");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1)
{
	auto shape = make_sphere(ax, r, angle1, "sphere");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1,
	const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1,
	double angle2)
{
	auto shape = make_sphere(ax, r, angle1, angle2, "sphere");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1,
	double angle2, const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1,
	double angle2, double angle3)
{
	auto shape = make_sphere(ax, r, angle1, angle2, angle3, "sphere");
	return {std::move(shape)};
}

tnbLib::api::cad::Shape tnbLib::api::cad::make_sphere(const gp_Ax2& ax, double r, double angle1,
	double angle2, double angle3, const std::string& name)
{
	auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2, angle3));
	shape->SetIndex(0);
	shape->SetName(name);
	return {std::move(shape)};
}

void tnbLib::api::cad::export_to_step(const Shape& shape, const std::string& name)
{
	Cad_Tools::ExportToSTEP(shape.shape->Shape(), name);
}

void tnbLib::api::cad::export_to_iges(const Shape& shape, const std::string& name,
	const std::string& unit)
{
	Cad_Tools::ExportToIGES(unit, shape.shape->Shape(), name);
}

void tnbLib::api::cad::save_to(const Shape& shape, const std::string& name, unsigned short verbose)
{
	file::CheckExtension(name);
	file::SaveTo(shape.shape, name + Cad_Shape::extension, verbose);
}


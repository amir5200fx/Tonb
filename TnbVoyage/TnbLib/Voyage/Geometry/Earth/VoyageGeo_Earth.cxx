#include <VoyageGeo_Earth.hxx>

#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomSurface.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <BRep_Tool.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>

const Standard_Real tnbLib::VoyageGeo_Earth::Radius = 6371.0;

tnbLib::VoyageGeo_Earth::VoyageGeo_Earth()
{
	auto shape = Cad_ShapeTools::Sphere(gp::XOY(), Radius);
	theGeometry_ = std::make_shared<Cad_Shape>(0, "earth", std::move(shape));
}

std::shared_ptr<tnbLib::Cad_GeomSurface> 
tnbLib::VoyageGeo_Earth::Surface() const
{
	Debug_Null_Pointer(theGeometry_);
	auto faces = Cad_Tools::RetrieveFaces(theGeometry_->Shape());
	Debug_If_Condition(faces.size() NOT_EQUAL 1);
	const auto forwardFace = 
		TopoDS::Face(faces.at(0).Oriented(TopAbs_FORWARD));
	TopLoc_Location Location;
	auto unbounded = BRep_Tool::Surface(forwardFace, Location);
	Standard_Real u0, v0, u1, v1;
	unbounded->Bounds(u0, u1, v0, v1);
	Entity2d_Box b(Pnt2d(u0, v0), Pnt2d(u1, v1));
	auto geometry =
		std::make_shared<Cad_GeomSurface>(Cad_Tools::ConvertToTrimmed(unbounded, b));
	return std::move(geometry);
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::VoyageGeo_Earth::Periods() const
{
	auto geom = Surface();
	auto b = geom->ParametricBoundingBox();
	Standard_Real dx, dy;
	b.Length(dx, dy);
	auto t = std::make_pair(dx, dy);
	return std::move(t);
}
#include <Mesh2d_SizeMapPolygon.hxx>

#include <Geo_BoxTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>

tnbLib::Entity2d_Box
tnbLib::Mesh2d_SizeMapPolygon::CalcBoundingBox() const
{
	return Geo_BoxTools::GetBox(theVolume_->Points(), 0);
}

Standard_Boolean tnbLib::Mesh2d_SizeMapPolygon::IsPolygon() const
{
	return Standard_True;
}

void tnbLib::Mesh2d_SizeMapPolygon::Perform()
{
	BoundaryRef() = theVolume_;
	Mesh2d_SizeMapVolume::Perform();
}

#include <GeoTop2d_Point3d.hxx>

std::shared_ptr<tnbLib::GeoTop2d_Point> 
tnbLib::GeoTop2d_Point3d::Copy() const
{
	auto pt = std::make_shared<GeoTop2d_Point3d>(Coord());
	return std::move(pt);
}
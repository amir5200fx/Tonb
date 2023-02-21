#include <GeoTop2d_Point2d.hxx>

std::shared_ptr<tnbLib::GeoTop2d_Point> 
tnbLib::GeoTop2d_Point2d::Copy() const
{
	auto pt = std::make_shared<GeoTop2d_Point2d>(Coord());
	return std::move(pt);
}
#include <Geo2d_MetricPrcsrUniSize.hxx>

const std::string tnbLib::Geo2d_MetricPrcsrUniSize::extension = ".mprcsr2d";

tnbLib::Entity2d_Box 
tnbLib::Geo2d_MetricPrcsrUniSize::BoundingBox() const
{
	return SizeFunction()->BoundingBox();
}
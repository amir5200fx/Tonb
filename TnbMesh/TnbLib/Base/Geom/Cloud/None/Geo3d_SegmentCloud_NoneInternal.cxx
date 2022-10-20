#include <Geo3d_SegmentCloud_NoneInternal.hxx>

#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Real>
tnbLib::Geo3d_SegmentCloud_NoneInternal::CalcCloud
(
	const std::vector<Standard_Real> & thePoly
) const
{
	return thePoly;
}
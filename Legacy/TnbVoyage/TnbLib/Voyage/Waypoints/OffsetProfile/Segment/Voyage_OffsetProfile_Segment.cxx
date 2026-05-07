#include <Voyage_OffsetProfile_Segment.hxx>

#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Voyage_OffsetProfile_Segment::Geometry
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	auto curve = std::make_shared<Pln_Curve>(std::move(geom));
	return std::move(curve);
}
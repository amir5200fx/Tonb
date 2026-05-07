#include <PtdModel_SectionCurve.hxx>

tnbLib::PtdModel_SectionCurve::PtdModel_SectionCurve
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: PtdModel_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::PtdModel_SectionCurve::PtdModel_SectionCurve
(
	const Handle(Geom2d_Curve)& theGeometry
)
	: theGeometry_(theGeometry)
{
	// empty body
}

tnbLib::PtdModel_SectionCurve::PtdModel_SectionCurve
(
	Handle(Geom2d_Curve)&& theGeometry
)
	: theGeometry_(std::move(theGeometry))
{
	// empty body
}
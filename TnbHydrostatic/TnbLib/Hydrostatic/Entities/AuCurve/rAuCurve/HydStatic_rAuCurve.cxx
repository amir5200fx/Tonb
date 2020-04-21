#include <HydStatic_rAuCurve.hxx>

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theCurve)
{
}

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theName, theCurve)
{
}
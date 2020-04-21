#include <HydStatic_hAuCurve.hxx>

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theCurve)
{
}

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theName, theCurve)
{
}
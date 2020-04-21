#include <HydStatic_WDiffCurve.hxx>

tnbLib::HydStatic_WDiffCurve::HydStatic_WDiffCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

tnbLib::HydStatic_WDiffCurve::HydStatic_WDiffCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_WDiffCurve::HydStatic_WDiffCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}
#include <HydStatic_AuCurve.hxx>

tnbLib::HydStatic_AuCurve::HydStatic_AuCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

tnbLib::HydStatic_AuCurve::HydStatic_AuCurve
(
	const Handle(Geom2d_Curve) && theCurve
)
	: HydStatic_HydCurve(std::move(theCurve))
{
}

tnbLib::HydStatic_AuCurve::HydStatic_AuCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_AuCurve::HydStatic_AuCurve
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}
#include <HydStatic_hArmCurve.hxx>

tnbLib::HydStatic_hArmCurve::HydStatic_hArmCurve
(
	Handle(Geom2d_Curve) && theCurve
)
	: HydStatic_ArmCurve(std::move(theCurve))
{
	// empty body
}

tnbLib::HydStatic_hArmCurve::HydStatic_hArmCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_ArmCurve(0, "heeling arm curve", theCurve)
{
	// empty body
}

tnbLib::HydStatic_hArmCurve::HydStatic_hArmCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_ArmCurve(theIndex, theName, std::move(theCurve))
{
	// empty body
}

tnbLib::HydStatic_hArmCurve::HydStatic_hArmCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_ArmCurve(theIndex, theName, theCurve)
{
	// empty body
}
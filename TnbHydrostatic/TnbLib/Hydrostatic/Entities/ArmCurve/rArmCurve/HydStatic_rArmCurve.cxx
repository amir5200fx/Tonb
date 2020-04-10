#include <HydStatic_rArmCurve.hxx>

tnbLib::HydStatic_rArmCurve::HydStatic_rArmCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_ArmCurve(0, "righting arm curve", theCurve)
{
}

tnbLib::HydStatic_rArmCurve::HydStatic_rArmCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_ArmCurve(theIndex, "righting arm curve", theCurve)
{
}

tnbLib::HydStatic_rArmCurve::HydStatic_rArmCurve
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_ArmCurve(theIndex, theName, theCurve)
{
}
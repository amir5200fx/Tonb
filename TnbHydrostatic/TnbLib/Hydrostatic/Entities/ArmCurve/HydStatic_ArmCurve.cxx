#include <HydStatic_ArmCurve.hxx>

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_ArmCurve::HydStatic_ArmCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}
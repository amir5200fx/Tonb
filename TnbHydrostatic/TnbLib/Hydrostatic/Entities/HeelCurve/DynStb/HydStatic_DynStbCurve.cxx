#include <HydStatic_DynStbCurve.hxx>

tnbLib::HydStatic_DynStbCurve::HydStatic_DynStbCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theCurve)
{
}

tnbLib::HydStatic_DynStbCurve::HydStatic_DynStbCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_DynStbCurve::HydStatic_DynStbCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theIndex, theName, theCurve)
{
}
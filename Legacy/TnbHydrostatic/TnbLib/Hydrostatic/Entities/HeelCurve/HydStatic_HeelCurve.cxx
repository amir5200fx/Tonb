#include <HydStatic_HeelCurve.hxx>

tnbLib::HydStatic_HeelCurve::HydStatic_HeelCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

//tnbLib::HydStatic_HeelCurve::HydStatic_HeelCurve
//(
//	const Standard_Integer theIndex,
//	const Handle(Geom2d_Curve)& theCurve
//)
//	: HydStatic_HydCurve(theIndex, theCurve)
//{
//}

tnbLib::HydStatic_HeelCurve::HydStatic_HeelCurve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}
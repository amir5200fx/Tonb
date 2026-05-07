#include <HydStatic_StaticStbCurve.hxx>

tnbLib::HydStatic_StaticStbCurve::HydStatic_StaticStbCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theCurve)
{
}

//tnbLib::HydStatic_StaticStbCurve::HydStatic_StaticStbCurve
//(
//	const Standard_Integer theIndex, 
//	const Handle(Geom2d_Curve)& theCurve
//)
//	: HydStatic_HeelCurve(theIndex, theCurve)
//{
//}

tnbLib::HydStatic_StaticStbCurve::HydStatic_StaticStbCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theIndex, theName, theCurve)
{
}
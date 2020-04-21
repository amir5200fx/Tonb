#include <HydStatic_DFldCurve.hxx>

tnbLib::HydStatic_DFldCurve::HydStatic_DFldCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theCurve)
{
}

tnbLib::HydStatic_DFldCurve::HydStatic_DFldCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_DFldCurve::HydStatic_DFldCurve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HeelCurve(theIndex, theName, theCurve)
{
}
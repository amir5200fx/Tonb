#include <HydStatic_HydCurve.hxx>

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	Handle(Geom2d_Curve) && theCurve
)
	: theGeom_(std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: theGeom_(theCurve)
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_Entity(theIndex, theName)
	, theGeom_(std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_Entity(theIndex, theName)
	, theGeom_(theCurve)
{
	//- empty body
}
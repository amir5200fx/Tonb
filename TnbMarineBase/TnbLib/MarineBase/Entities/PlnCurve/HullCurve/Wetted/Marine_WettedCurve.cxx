#include <Marine_WettedCurve.hxx>

tnbLib::Marine_WettedCurve::Marine_WettedCurve()
{
}

tnbLib::Marine_WettedCurve::Marine_WettedCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theIndex, theGeom)
{
}

tnbLib::Marine_WettedCurve::Marine_WettedCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theGeom)
{
}

tnbLib::Marine_WettedCurve::Marine_WettedCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_HullCurve(theIndex, theName, theGeom)
{
}
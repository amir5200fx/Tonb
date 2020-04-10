#include <Marine_HullCurve.hxx>

tnbLib::Marine_HullCurve::Marine_HullCurve()
{
}

tnbLib::Marine_HullCurve::Marine_HullCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_PlnCurve(theIndex, theGeom)
{
}

tnbLib::Marine_HullCurve::Marine_HullCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_PlnCurve(theGeom)
{
}

tnbLib::Marine_HullCurve::Marine_HullCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theGeom
)
	: Marine_PlnCurve(theIndex, theName, theGeom)
{
}
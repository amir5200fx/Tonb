#include <Marine_PlnCurve.hxx>

tnbLib::Marine_PlnCurve::Marine_PlnCurve()
{
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theIndex, theGeom)
{
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theGeom)
{
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theIndex, theName, theGeom)
{
}
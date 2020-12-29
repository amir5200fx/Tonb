#include <Marine_PlnCurve.hxx>

tnbLib::Marine_PlnCurve::Marine_PlnCurve()
{
	// empty body
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theIndex, theGeom)
{
	// empty body
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theGeom)
{
	// empty body
}

tnbLib::Marine_PlnCurve::Marine_PlnCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theGeom
)
	: Pln_Curve(theIndex, theName, theGeom)
{
	// empty body
}
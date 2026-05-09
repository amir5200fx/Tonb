#include <Marine_GraphCurve.hxx>

#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Marine_GraphCurve::CheckCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const char * theName
)
{
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn(theName) << endl
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
}

tnbLib::Marine_GraphCurve::Marine_GraphCurve
(
	const Handle(Geom2d_Curve) theCurve
)
	: theCurve_(theCurve)
{
	CheckCurve(Curve(), "Marine_GraphCurve::Marine_GraphCurve()");
}

tnbLib::Marine_GraphCurve::Marine_GraphCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve
)
	: Marine_GraphEntity(theIndex)
	, theCurve_(theCurve)
{
	CheckCurve(Curve(), "Marine_GraphCurve::Marine_GraphCurve()");
}

tnbLib::Marine_GraphCurve::Marine_GraphCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: Marine_GraphEntity(theIndex, theName)
	, theCurve_(theCurve)
{
	CheckCurve(Curve(), "Marine_GraphCurve::Marine_GraphCurve()");
}
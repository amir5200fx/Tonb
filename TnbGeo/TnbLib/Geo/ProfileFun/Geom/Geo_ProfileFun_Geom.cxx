#include <Geo_ProfileFun_Geom.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theLower,
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theLower, theUpper)
	, theCurve_(theCurve)
{
}

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	Handle(Geom2d_Curve) && theCurve, 
	const Standard_Real theLower,
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theLower, theUpper)
	, theCurve_(std::move(theCurve))
{
}

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real theLower, 
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theIndex, theLower, theUpper)
	, theCurve_(theCurve)
{
}

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	const Standard_Integer theIndex, 
	Handle(Geom2d_Curve) && theCurve, 
	const Standard_Real theLower,
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theIndex, theLower, theUpper)
	, theCurve_(std::move(theCurve))
{
}

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve, 
	const Standard_Real theLower, 
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theIndex, theName, theLower, theUpper)
	, theCurve_(theCurve)
{
}

tnbLib::geoLib::ProfileFun_Geom::ProfileFun_Geom
(
	const Standard_Integer theIndex, 
	const word & theName, 
	Handle(Geom2d_Curve) && theCurve,
	const Standard_Real theLower,
	const Standard_Real theUpper
)
	: Geo_ProfileFun(theIndex, theName, theLower, theUpper)
	, theCurve_(std::move(theCurve))
{
}

#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_Line.hxx>

Standard_Real 
tnbLib::geoLib::ProfileFun_Geom::Value
(
	const Standard_Real x
) const
{
	Debug_If_Condition(Upper() <= Lower());

	if (NOT IsInside(x))
	{
		FatalErrorIn(FunctionSIG)
			<< "outside of the bounds: " << endl
			<< " - lower = " << Lower() << endl
			<< " - upper = " << Upper() << endl
			<< " - x = " << x << endl
			<< abort(FatalError);
	}

	if (const auto lower = Curve()->Value(Curve()->FirstParameter()).Y(); x IS_EQUAL lower)
	{
		return lower;
	}
	if (const auto upper = Curve()->Value(Curve()->LastParameter()).Y(); x IS_EQUAL upper)
	{
		return upper;
	}

	Geom2dAPI_InterCurveCurve Intersection;
	Handle(Geom2d_Line) Line =
		new Geom2d_Line(gp_Pnt2d(x, 0), gp_Vec2d(0, 1));

	Intersection.Init(Curve(), Line, 1.0e-6);

	if (NOT Intersection.NbPoints())
	{
		FatalErrorIn(FunctionSIG)
			<< " No Intersection has been found"
			<< abort(FatalError);
	}

	if (Intersection.NbPoints() != 1)
	{
		FatalErrorIn(FunctionSIG)
			<< " More than one intersection point has been found"
			<< abort(FatalError);
	}
	return Intersection.Point(1).Y();
}
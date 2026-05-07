#include <HydStatic_FillCurve.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::HydStatic_FillCurve::HydStatic_FillCurve
(
	Handle(Geom2d_Curve) && theCurve
)
	: HydStatic_HydCurve(std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_FillCurve::HydStatic_FillCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
	//- empty body
}

tnbLib::HydStatic_FillCurve::HydStatic_FillCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve) && theCurve
)
	: HydStatic_HydCurve(theIndex, theName, std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_FillCurve::HydStatic_FillCurve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
	//- empty body
}

Standard_Boolean 
tnbLib::HydStatic_FillCurve::IsLevelIntersect
(
	const Standard_Real theLevel
) const
{
	return INSIDE(theLevel, MinLevel(), MaxLevel());
}

Standard_Boolean 
tnbLib::HydStatic_FillCurve::IsVolumeIntersect
(
	const Standard_Real theVolume
) const
{
	return INSIDE(theVolume, MinVolume(), MaxVolume());
}

Standard_Real 
tnbLib::HydStatic_FillCurve::MinLevel() const
{
	const auto pt = FirstCoord();
	return pt.X();
}

Standard_Real 
tnbLib::HydStatic_FillCurve::MaxLevel() const
{
	const auto pt = LastCoord();
	return pt.X();
}

Standard_Real 
tnbLib::HydStatic_FillCurve::MinVolume() const
{
	const auto pt = FirstCoord();
	return pt.Y();
}

Standard_Real 
tnbLib::HydStatic_FillCurve::MaxVolume() const
{
	const auto pt = LastCoord();
	return pt.Y();
}

Standard_Real 
tnbLib::HydStatic_FillCurve::Volume
(
	const Standard_Real theLevel
) const
{
	if (NOT IsLevelIntersect(theLevel))
	{
		FatalErrorIn("Standard_Real Volume(const Standard_Real theLevel) const")
			<< "Found no intersection" << endl
			<< " - lower: " << MinLevel() << ", upper: " << MaxLevel() << endl
			<< " - x: " << theLevel << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(theLevel, 0), gp_Dir2d(0, 1));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Volume(const Standard_Real theLevel) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}
	auto value = Int.Point(1);
	return value.Y();
}

Standard_Real 
tnbLib::HydStatic_FillCurve::Level
(
	const Standard_Real theVolume
) const
{
	if (NOT IsLevelIntersect(theVolume))
	{
		FatalErrorIn("Standard_Real Volume(const Standard_Real theLevel) const")
			<< "Found no intersection" << endl
			<< " - lower: " << MinVolume() << ", upper: " << MaxVolume() << endl
			<< " - x: " << theVolume << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(0, theVolume), gp_Dir2d(1, 0));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Volume(const Standard_Real theLevel) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}
	auto value = Int.Point(1);
	return value.X();
}
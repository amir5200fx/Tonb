#include <HydStatic_CrsCurve.hxx>

#include <Pnt2d.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theHeel
)
	: HydStatic_HydCurve(0, "cross-curve", theCurve)
	, theHeel_(theHeel)
{
}

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	const Standard_Integer theIndex, 
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theHeel
)
	: HydStatic_HydCurve(theIndex, "cross-curve", theCurve)
	, theHeel_(theHeel)
{
}

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theHeel
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
	, theHeel_(theHeel)
{
}

Standard_Boolean 
tnbLib::HydStatic_CrsCurve::IsIntersect
(
	const Standard_Real theVolume
) const
{
	return INSIDE(theVolume, LeverArm0(), LeverArm1());
}

Standard_Real 
tnbLib::HydStatic_CrsCurve::LeverArm0() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p0 = geom.Value(geom.FirstParameter());
	return p0.X();
}

Standard_Real 
tnbLib::HydStatic_CrsCurve::LeverArm1() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p1 = geom.Value(geom.LastParameter());
	return p1.X();
}

Standard_Real
tnbLib::HydStatic_CrsCurve::Value
(
	const Standard_Real theVolume
) const
{
	if (NOT IsIntersect(theVolume))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Found no intersection" << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(theVolume, 0), gp_Dir2d(0, 1));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}

	auto value = Int.Point(0);
	return value.Y();
}
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
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(0, "cross-curve", theCurve)
{
	// empty body
}

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
	// empty body
}

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_HydCurve(0, "cross-curve", std::move(theCurve))
{
	// empty body
}

tnbLib::HydStatic_CrsCurve::HydStatic_CrsCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, std::move(theCurve))
{
	// empty body
}

Standard_Boolean 
tnbLib::HydStatic_CrsCurve::IsIntersect
(
	const Standard_Real theVolume
) const
{
	return INSIDE(theVolume, Dispv0(), Dispv1());
}

Standard_Real 
tnbLib::HydStatic_CrsCurve::LeverArm0() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p0 = geom.Value(geom.FirstParameter());
	return p0.Y();
}

Standard_Real 
tnbLib::HydStatic_CrsCurve::LeverArm1() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p1 = geom.Value(geom.LastParameter());
	return p1.Y();
}

Standard_Real 
tnbLib::HydStatic_CrsCurve::Dispv0() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p0 = geom.Value(geom.FirstParameter());
	return p0.X();
}

Standard_Real
tnbLib::HydStatic_CrsCurve::Dispv1() const
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
		FatalErrorIn("Standard_Real Value(const Standard_Real theVolume) const")
			<< "Found no intersection" << endl
			<< " - lower: " << Dispv0() << ", upper: " << Dispv1() << endl
			<< " - x: " << theVolume << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(theVolume, 0), gp_Dir2d(0, 1));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theVolume) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}
	auto value = Int.Point(1);
	return value.Y();
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::HydStatic_CrsCurve::ValueP
(
	const Standard_Real theVolume
) const
{
	if (NOT IsIntersect(theVolume))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Found no intersection" << endl
			<< " - lower: " << Dispv0() << ", upper: " << Dispv1() << endl
			<< " - x: " << theVolume << endl
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
	auto value = Int.Point(1);
	auto par = Int.Intersector().Point(1).ParamOnSecond();
	auto t = std::make_pair(value.Y(), par);
	return std::move(t);
}
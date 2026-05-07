#include <HydStatic_BnjCurve.hxx>

#include <Pnt2d.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::HydStatic_BnjCurve::HydStatic_BnjCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(0, "bonjean curve", theCurve)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::HydStatic_BnjCurve::HydStatic_BnjCurve
(
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_HydCurve(0, "bonjean curve", std::move(theCurve))
{
	// empty body [6/3/2021 Amir]
}

tnbLib::HydStatic_BnjCurve::HydStatic_BnjCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, "bonjean curve", theCurve)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::HydStatic_BnjCurve::HydStatic_BnjCurve
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
	// empty body [6/3/2021 Amir]
}

Standard_Boolean 
tnbLib::HydStatic_BnjCurve::IsIntersect
(
	const Standard_Real theT
) const
{
	return INSIDE(theT, A0(), A1());
}

Standard_Real 
tnbLib::HydStatic_BnjCurve::A0() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p0 = geom.Value(geom.FirstParameter());
	return p0.Y();
}

Standard_Real 
tnbLib::HydStatic_BnjCurve::A1() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto p1 = geom.Value(geom.LastParameter());
	return p1.Y();
}

Standard_Real 
tnbLib::HydStatic_BnjCurve::Value
(
	const Standard_Real theT
) const
{
	if (NOT IsIntersect(theT))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Found no intersection" << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l = 
		new Geom2d_Line(gp_Pnt2d(0, theT), gp_Dir2d(1, 0));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());	
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}

	auto value = Int.Point(0);
	return value.X();
}
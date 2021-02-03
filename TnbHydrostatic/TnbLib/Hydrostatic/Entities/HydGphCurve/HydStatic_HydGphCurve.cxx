#include <HydStatic_HydGphCurve.hxx>

#include <Pnt2d.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

Standard_Boolean 
tnbLib::HydStatic_HydGphCurve::IsIntersect
(
	const Standard_Real theT
) const
{
	return INSIDE(theT, Draft0(), Draft1());
}

Standard_Real 
tnbLib::HydStatic_HydGphCurve::Draft0() const
{
	auto p0 = FirstCoord();
	return p0.X();
}

Standard_Real 
tnbLib::HydStatic_HydGphCurve::Draft1() const
{
	auto p1 = LastCoord();
	return p1.X();
}

Standard_Real 
tnbLib::HydStatic_HydGphCurve::Draft
(
	const Standard_Real theT
) const
{
	if (NOT IsIntersect(theT))
	{
		FatalErrorIn("Standard_Real Value(const Standard_Real theT) const")
			<< "Found no intersection" << endl
			<< " - lower: " << Draft0() << ", upper: " << Draft1() << endl
			<< " - x: " << theT << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Line) l =
		new Geom2d_Line(gp_Pnt2d(0, theT), gp_Dir2d(1, 0));
	Debug_Null_Pointer(l);

	Geom2dAPI_InterCurveCurve Int(l, Geometry());
	if (Int.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn("Standard_Real Draft(const Standard_Real theT) const")
			<< "Invalid data" << endl
			<< abort(FatalError);
	}
	auto value = Int.Point(1);
	return value.X();
}
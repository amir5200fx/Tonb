#include <Pln_CurveTools.hxx>

#include <Pln_Tools.hxx>

#include <Entity2d_Triangulation.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	gp_Vec2d V(theP0, theP1);
	Handle(Geom2d_Curve) C = new Geom2d_Line(theP0, gp_Dir2d(V));

	Geom2dAPI_ProjectPointOnCurve Projection;
	Projection.Init(theP0, C);

	const auto u0 = Projection.LowerDistanceParameter();

	Projection.Init(theP1, C);

	const auto u1 = Projection.LowerDistanceParameter();

	auto trimmed = Pln_Tools::ConvertToTrimmedCurve(C, u0, u1);
	return std::move(trimmed);
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const gp_Ax22d & A, 
	const Standard_Real Radius
)
{
	Handle(Geom2d_Curve) Circle = new Geom2d_Circle(A, Radius);
	auto trimmed = Pln_Tools::ConvertToTrimmedCurve
	(
		Circle, Circle->FirstParameter(),
		Circle->LastParameter());

	return std::move(trimmed);
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const gp_Ax2d & A, 
	const Standard_Real Radius,
	const Standard_Boolean Sense
)
{
	auto g = gp_Ax22d(A, Sense);
	auto c = MakeCircle(g, Radius);

	return std::move(c);
}


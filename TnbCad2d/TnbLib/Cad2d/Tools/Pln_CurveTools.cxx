#include <Pln_CurveTools.hxx>

#include <Entity2d_Triangulation.hxx>

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

	auto trimmed = ConvertToTrimmedCurve(C, u0, u1);
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
	auto trimmed = ConvertToTrimmedCurve
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

std::shared_ptr<Geom2dAPI_InterCurveCurve> 
tnbLib::Pln_CurveTools::Intersection
(
	const Handle(Geom2d_Curve)& theCurve0,
	const Handle(Geom2d_Curve)& theCurve1, 
	const Standard_Real theTol
)
{
	auto trimmed0 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve0);
	if (NOT trimmed0)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto trimmed1 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve1);
	if (NOT trimmed1)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto Inter = std::make_shared<Geom2dAPI_InterCurveCurve>(theCurve0, theCurve1, theTol);
	Debug_Null_Pointer(Inter);

	return std::move(Inter);
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::ConvertToTrimmedCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1
)
{
	Handle(Geom2d_Curve) trimmed =
		new Geom2d_TrimmedCurve(theCurve, theU0, theU1);
	return std::move(trimmed);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Pln_CurveTools::ParametricTriangulation
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Standard_Integer theNx,
	const Standard_Integer theNy
)
{
	if (theNx < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (theNy < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto Dx = theP1.X() - theP0.X();
	const auto Dy = theP1.Y() - theP0.Y();

	const auto dx = Dx / (Standard_Real)theNx;
	const auto dy = Dy / (Standard_Real)theNy;

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(theNx*theNy);

	auto& indices = tri->Connectivity();
	indices.reserve((theNx - 1)*(theNy - 1) * 2);

	Standard_Integer k = 0;
	for (auto i = 0; i < theNx; i++)
	{
		for (auto j = 0; j < theNy; j++)
		{
			auto P0 = theP0 + Pnt2d(i*dx, j*dy);
			/*auto P1 = P0 + Pnt2d(dx, 0);
			auto P2 = P0 + Pnt2d(dx, dy);
			auto P3 = P0 + Pnt2d(0, dy);*/
			//cout << i << ", " << j << "  " << P0 << std::endl;
			pts.push_back(std::move(P0));
		}
	}

	for (auto i = 0; i < theNx - 1; i++)
	{
		for (auto j = 0; j < theNy - 1; j++)
		{
			auto i0 = j * theNx + i + 1;
			auto i1 = j * theNx + i + 2;
			auto i2 = (j + 1)*theNx + i + 2;

			auto j0 = i0;
			auto j1 = i2;
			auto j2 = (j + 1)*theNx + i + 1;

			connectivity::triple I0, I1;
			I0.Value(0) = i0;
			I0.Value(1) = i1;
			I0.Value(2) = i2;

			I1.Value(0) = j0;
			I1.Value(1) = j1;
			I1.Value(2) = j2;

			indices.push_back(std::move(I0));
			indices.push_back(std::move(I1));
		}
	}
	return std::move(tri);
}
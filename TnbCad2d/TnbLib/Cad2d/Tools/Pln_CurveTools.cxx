#include <Pln_CurveTools.hxx>

#include <Vec2d.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <TecPlot.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

Handle(Geom2d_Curve) 
tnbLib::Pln_CurveTools::Interpolation
(
	const std::vector<Pnt2d>& theQ, 
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points to interpolate" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, theQ.size());
	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Q->SetValue(K + 1, x);

		++K;
	}

	Geom2dAPI_Interpolate interp(Q, thePeriodic, theTol);
	interp.Perform();

	return interp.Curve();
}

Handle(Geom2d_Curve) 
tnbLib::Pln_CurveTools::Interpolation
(
	const std::vector<Pnt2d>& theQ,
	const Vec2d & theFirst,
	const Vec2d & theLast,
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol, 
	const Standard_Boolean theScale
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points to interpolate" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt2d) Q = new TColgp_HArray1OfPnt2d(1, theQ.size());
	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Q->SetValue(K + 1, x);

		++K;
	}

	Geom2dAPI_Interpolate interp(Q, thePeriodic, theTol);

	interp.Load(theFirst, theLast, theScale);
	interp.Perform();

	const auto& curve = interp.Curve();

	return interp.Curve();
}

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

void tnbLib::Pln_CurveTools::ExportToPlt
(
	const Handle(Geom2d_Curve)& theCurve,
	OFstream& File,
	const Standard_Integer n
)
{
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("void Pln_CurveTools::ExportToPlt(Args...)")
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
	const auto du = (theCurve->LastParameter() - theCurve->FirstParameter()) / (Standard_Real)n;
	const auto u0 = theCurve->FirstParameter();
	std::vector<Pnt2d> pts;
	pts.reserve(n + 1);

	for (auto i = 0; i <= n; i++)
	{
		auto pt = theCurve->Value(u0 + i * du);
		pts.push_back(std::move(pt));
	}

	Io::ExportCurve(pts, File);
}
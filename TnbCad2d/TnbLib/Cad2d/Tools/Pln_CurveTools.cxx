#include <Pln_CurveTools.hxx>

#include <Vec2d.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
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

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCE2d_MakeArcOfHyperbola.hxx>
#include <GCE2d_MakeArcOfParabola.hxx>
#include <GCE2d_MakeCircle.hxx>
#include <GCE2d_MakeEllipse.hxx>

#include <algorithm>

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::Trim
(
	const Handle(Geom2d_Curve) theCurve,
	const Standard_Real theP0, 
	const Standard_Real theP1
)
{
	if (theP0 >= theP1)
	{
		FatalErrorIn("Handle(Geom2d_Curve) Trim(Args...)")
			<< "invalid data: p0 >= p1" << endl
			<< abort(FatalError);
	}

	const auto p0 = std::max(theP0, theCurve->FirstParameter());
	const auto p1 = std::min(theP1, theCurve->LastParameter());

	Handle(Geom2d_TrimmedCurve) t = new Geom2d_TrimmedCurve(theCurve, p0, p1);
	return std::move(t);
}

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

	Handle(TColgp_HArray1OfPnt2d) Q =
		new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
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

	Handle(TColgp_HArray1OfPnt2d) Q = 
		new TColgp_HArray1OfPnt2d(1, (Standard_Integer)theQ.size());
	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Q->SetValue(K + 1, x);

		++K;
	}

	try
	{
		Geom2dAPI_Interpolate interp(Q, thePeriodic, theTol);

		interp.Load(theFirst, theLast, theScale);
		interp.Perform();

		return interp.Curve();
	}
	catch (const StdFail_NotDone& f)
	{
		FatalErrorIn(FunctionSIG)
			<< "catch an exception in 'Geom2dAPI_Interpolate' algorithm" << endl
			<< " message: " << f.GetMessageString() << endl;
		return nullptr;
	}
}

//Handle(Geom2d_Curve)
//tnbLib::Pln_CurveTools::MakeSegment
//(
//	const Pnt2d & theP0,
//	const Pnt2d & theP1
//)
//{
//	gp_Vec2d V(theP0, theP1);
//	Handle(Geom2d_Curve) C = new Geom2d_Line(theP0, gp_Dir2d(V));
//
//	Geom2dAPI_ProjectPointOnCurve Projection;
//	Projection.Init(theP0, C);
//
//	const auto u0 = Projection.LowerDistanceParameter();
//
//	Projection.Init(theP1, C);
//
//	const auto u1 = Projection.LowerDistanceParameter();
//
//	auto trimmed = Pln_Tools::ConvertToTrimmedCurve(C, u0, u1);
//	return std::move(trimmed);
//}
//
//Handle(Geom2d_Curve)
//tnbLib::Pln_CurveTools::MakeCircle
//(
//	const gp_Ax22d & A, 
//	const Standard_Real Radius
//)
//{
//	Handle(Geom2d_Curve) Circle = new Geom2d_Circle(A, Radius);
//	auto trimmed = Pln_Tools::ConvertToTrimmedCurve
//	(
//		Circle, Circle->FirstParameter(),
//		Circle->LastParameter());
//
//	return std::move(trimmed);
//}
//
//Handle(Geom2d_Curve)
//tnbLib::Pln_CurveTools::MakeCircle
//(
//	const gp_Ax2d & A, 
//	const Standard_Real Radius,
//	const Standard_Boolean Sense
//)
//{
//	auto g = gp_Ax22d(A, Sense);
//	auto c = MakeCircle(g, Radius);
//
//	return std::move(c);
//}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeSegment
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeSegment maker(theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircArc
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircArc
(
	const Pnt2d & theP0,
	const Vec2d & theV0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theP0, theV0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircArc
(
	const gp_Circ2d & theCirc,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircArc
(
	const gp_Circ2d & theCirc,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfCircle maker(theCirc, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeElipsArc
(
	const gp_Elips2d & theElips,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfEllipse maker(theElips, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeHyprArc
(
	const gp_Hypr2d & theHypr,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfHyperbola maker(theHypr, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeParbArc
(
	const gp_Parab2d & theParab,
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theAlpha0, theAlpha1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeParbArc
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	GCE2d_MakeArcOfParabola maker(theParab, theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const gp_Circ2d & C
)
{
	GCE2d_MakeCircle maker(C);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const gp_Circ2d & C,
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(C, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	GCE2d_MakeCircle maker(theP0, theP1, theP2);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const Pnt2d & theC,
	const Standard_Real theRadius
)
{
	GCE2d_MakeCircle maker(theC, theRadius);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeCircle
(
	const Pnt2d & theC,
	const Pnt2d & theP
)
{
	GCE2d_MakeCircle maker(theC, theP);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeEllipse
(
	const gp_Elips2d & E
)
{
	GCE2d_MakeEllipse maker(E);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}

Handle(Geom2d_Curve)
tnbLib::Pln_CurveTools::MakeEllipse
(
	const Pnt2d & theS0,
	const Pnt2d & theS1,
	const Pnt2d & theCenter
)
{
	GCE2d_MakeEllipse maker(theS0, theS1, theCenter);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
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
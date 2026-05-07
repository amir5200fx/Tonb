#include <AirfoilPx_PxThickProfile_t2.hxx>

#include <Airfoil_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Ray.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <StdFail_NotDone.hxx>

Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_CHORDLEN = 1.0;

Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_MAX = 0.1;
Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_MAX_LOC = 0.4;

Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_LEAD_STEEP_TIGHT1(0.5);
Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_LEAD_STEEP_TIGHT2(0.5);

Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_TRAIL_STEEP(PI / 6.0);
Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_TRAIL_STEEP_TIGHT(0.5);
Standard_Real tnbLib::profileLib::PxThick_t2::DEFAULT_TRAIL_STEEP_VELOCITY(0.5);

Standard_Real 
tnbLib::profileLib::PxThick_t2::Value(const Standard_Real x) const
{
	CheckDone((*this));
	const auto& c = Curve();
#ifdef _DEBUG	
	const auto x0 = c->FirstCoord().X();
	const auto x1 = c->LastCoord().X();
	if (NOT INSIDE(x, x0, x1))
	{
		FatalErrorIn(FunctionSIG)
			<< "out of range value has been detected." << endl
			<< " - lower: " << x0 << endl
			<< " - upper: " << x1 << endl
			<< " - value: " << x << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto [y, par] = Airfoil_Tools::xValue(x, c);
	return y;
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::profileLib::PxThick_t2::Curves() const
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.push_back(Curve());
	return std::move(curves);
}

std::vector<Standard_Real> 
tnbLib::profileLib::PxThick_t2::Spans() const
{
	auto spans = Airfoil_Tools::CalcSpans(Curves());
	return std::move(spans);
}

namespace tnbLib
{

	auto CalcIntersection(const Entity2d_Ray& hor, const Entity2d_Ray& ver, const Entity2d_Ray& r)
	{
		auto [pt1, cond1] = Geo_Tools::CalcIntersectionPoint_cgal(hor, r);
		if (cond1)
		{
			return std::move(pt1);
		}
		auto [pt2, cond2] = Geo_Tools::CalcIntersectionPoint_cgal(hor, r);
		if (cond2)
		{
			return std::move(pt2);
		}
		FatalErrorIn(FunctionSIG)
			<< "Invalid Geometry has been detected." << endl
			<< abort(FatalError);
		return Pnt2d(0, 0);
	}
}

void tnbLib::profileLib::PxThick_t2::Perform()
{
	static const Standard_Integer nbPoles = 7;

	Pnt2d P0(0, 0);
	Pnt2d P6(ChordLen(), 0);
	Pnt2d P3(MaxLoc(), Max());

	auto P1 = Geo_Tools::LinearInterpolate(P0, Pnt2d(0, Max()), LeadSteepTight1());
	auto P2 = Geo_Tools::LinearInterpolate(P3, Pnt2d(0, Max()), LeadSteepTight2());

	auto P4 = Geo_Tools::LinearInterpolate(P3, Pnt2d(ChordLen(), Max()), TrailSteepTight());

	Dir2d P6_dir(-std::cos(TrailSteep()), std::sin(TrailSteep()));
	Entity2d_Ray P6_ray(P6, P6_dir);

	Entity2d_Ray horRay(P4, gp::DX2d());
	Entity2d_Ray verRay(P4, -gp::DY2d());

	auto P5 = Geo_Tools::LinearInterpolate(CalcIntersection(horRay, verRay, P6_ray), P6, TrailSteepVelocity());

	TColgp_Array1OfPnt2d pnts(1, nbPoles);
	pnts.SetValue(1, P0);
	pnts.SetValue(2, P1);
	pnts.SetValue(3, P2);
	pnts.SetValue(4, P3);
	pnts.SetValue(5, P4);
	pnts.SetValue(6, P5);

	TColStd_Array1OfReal weights(1, nbPoles);
	for (Standard_Integer i = 1; i <= weights.Size(); i++)
	{
		weights.SetValue(i, 1.0);
	}

	TColStd_Array1OfReal knots(1, 3);
	static const auto du = (Standard_Real)0.5;
	knots.SetValue(1, 0.0);
	knots.SetValue(2, du);
	knots.SetValue(3, 1.0);

	TColStd_Array1OfInteger mults(1, 3);
	mults.SetValue(1, 4);
	mults.SetValue(2, 3);
	mults.SetValue(3, 4);

	try
	{
		auto geom = new Geom2d_BSplineCurve(pnts, weights, knots, mults, 3);
		auto curve = std::make_shared<Pln_Curve>(std::move(geom));
		theCurve_ = std::move(curve);
	}
	catch (const StdFail_NotDone& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	Change_IsDone() = Standard_True;
}
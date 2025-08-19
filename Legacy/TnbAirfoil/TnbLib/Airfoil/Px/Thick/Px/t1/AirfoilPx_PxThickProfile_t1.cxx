#include <AirfoilPx_PxThickProfile_t1.hxx>

#include <Airfoil_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <StdFail_NotDone.hxx>

Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_CHORDLEN = 1.0;

Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_MAX = 0.1;
Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_MAX_LOC = 0.4;

Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_LEAD_STEEP = 1.0;
Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_LEAD_STEEP_TIGHT = 0.0001;
Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_LEAD_STEEP_WEIGHT = 1.0;

Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_TRAIL_STEEP = 1.0;
Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_TRAIL_STEEP_TIGHT = 0.0001;
Standard_Real tnbLib::profileLib::PxThick_t1::DEFAULT_TRAIL_STEEP_WEIGHT = 1.0;

Standard_Real 
tnbLib::profileLib::PxThick_t1::Value(const Standard_Real x) const
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
tnbLib::profileLib::PxThick_t1::Curves() const
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.push_back(Curve());
	return std::move(curves);
}

std::vector<Standard_Real> 
tnbLib::profileLib::PxThick_t1::Spans() const
{
	auto spans = Airfoil_Tools::CalcSpans(Curves());
	return std::move(spans);
}

void tnbLib::profileLib::PxThick_t1::Perform()
{
	static const Standard_Integer nbPoles = 9;

	Pnt2d P0(0, 0);
	Pnt2d P8(ChordLen(), 0);
	Pnt2d P4(MaxLoc(), Max());

	auto P2 = Geo_Tools::LinearInterpolate(P4, Pnt2d(0, Max()), LeadSteep());
	auto P6 = Geo_Tools::LinearInterpolate(P4, Pnt2d(ChordLen(), Max()), TrailSteep());

	auto P1 = Geo_Tools::LinearInterpolate(P0, P2, LeadSteepTight());
	auto P3 = Geo_Tools::LinearInterpolate(P4, P2, LeadSteepTight());

	auto P5 = Geo_Tools::LinearInterpolate(P4, P6, TrailSteepTight());
	auto P7 = Geo_Tools::LinearInterpolate(P8, P6, TrailSteepTight());

	TColgp_Array1OfPnt2d pnts(1, nbPoles);
	pnts.SetValue(1, P0);
	pnts.SetValue(2, P1);
	pnts.SetValue(3, P2);
	pnts.SetValue(4, P3);
	pnts.SetValue(5, P4);
	pnts.SetValue(6, P5);
	pnts.SetValue(7, P6);
	pnts.SetValue(8, P7);
	pnts.SetValue(9, P8);

	TColStd_Array1OfReal weights(1, nbPoles);
	for (Standard_Integer i = 1; i <= weights.Size(); i++)
	{
		weights.SetValue(i, 1.0);
	}
	weights.SetValue(3, LeadSteepWeight());
	weights.SetValue(7, TrailSteepWeight());

	TColStd_Array1OfReal knots(1, 5);
	static const auto du = (Standard_Real)0.25;
	knots.SetValue(1, 0);
	knots.SetValue(2, du);
	knots.SetValue(3, 0.5);
	knots.SetValue(4, 0.5 + du);
	knots.SetValue(5, 1.0);

	TColStd_Array1OfInteger mults(1, 5);
	mults.SetValue(1, 4);
	mults.SetValue(2, 1);
	mults.SetValue(3, 3);
	mults.SetValue(4, 1);
	mults.SetValue(5, 4);

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
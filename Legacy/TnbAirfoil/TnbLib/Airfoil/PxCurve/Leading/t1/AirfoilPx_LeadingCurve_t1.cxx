#include <AirfoilPx_LeadingCurve_t1.hxx>

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

Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_NOSE_ANGLE(0.0);

Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_UPPER_TIGHT(0.5);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_UPPER_WEIGHT0(1.0);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_UPPER_WEIGHT1(1.0);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_UPPER_WEIGHT2(1.0);

Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_LOWER_TIGHT(0.5);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_LOWER_WEIGHT0(1.0);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_LOWER_WEIGHT1(1.0);
Standard_Real tnbLib::profileLib::LeadingCurve_t1::DEFAULT_LOWER_WEIGHT2(1.0);

void tnbLib::profileLib::LeadingCurve_t1::Perform()
{
	static const Standard_Integer nbPoles = 9;

	Pnt2d P0{ UpperMaxLoc(), UpperMax() };
	Pnt2d P4{ Xo(), Yo() };
	Pnt2d P8{ LowerMaxLoc(),LowerMax() };

	Entity2d_Ray upperRay_4{ P4,{std::sin(NoseAngle()),std::cos(NoseAngle())} };
	Entity2d_Ray ray_0{ P0,{-std::cos(UpperMaxAngle()),-std::sin(UpperMaxAngle())} };

	auto [P2, upperCorner_cond] = Geo_Tools::CalcIntersectionPoint_cgal(upperRay_4, ray_0);
	if (NOT upperCorner_cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to calculate the intersection point." << endl
			<< abort(FatalError);
	}

	Entity2d_Ray lowerRay_4{ P4,{-std::sin(NoseAngle()),-std::cos(NoseAngle())} };
	Entity2d_Ray ray_8{ P8,{-std::cos(LowerMaxAngle()), std::sin(LowerMaxAngle())} };

	auto [P6, lowerCorner_cond] = Geo_Tools::CalcIntersectionPoint_cgal(lowerRay_4, ray_8);
	if (NOT lowerCorner_cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to calculate the intersection point." << endl
			<< abort(FatalError);
	}

	auto P1 = Geo_Tools::LinearInterpolate(P0, P2, UpperTight());
	auto P3 = Geo_Tools::LinearInterpolate(P4, P2, UpperTight());

	auto P7 = Geo_Tools::LinearInterpolate(P8, P6, LowerTight());
	auto P5 = Geo_Tools::LinearInterpolate(P4, P6, LowerTight());

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

	weights.SetValue(2, UpperWeight0());
	weights.SetValue(3, UpperWeight1());
	weights.SetValue(4, UpperWeight2());

	weights.SetValue(6, LowerWeight0());
	weights.SetValue(7, LowerWeight1());
	weights.SetValue(8, LowerWeight2());

	TColStd_Array1OfReal knots(1, 5);
	static const auto du = (Standard_Real)0.25;
	knots.SetValue(1, 0);
	knots.SetValue(2, du);
	knots.SetValue(3, 2*du);
	knots.SetValue(4, 3 * du);
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
		CurveRef() = std::move(curve);
	}
	catch (const StdFail_NotDone& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	Change_IsDone() = Standard_True;
}
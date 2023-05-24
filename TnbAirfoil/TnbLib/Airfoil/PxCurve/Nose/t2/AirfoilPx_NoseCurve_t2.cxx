#include <AirfoilPx_NoseCurve_t2.hxx>

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

Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_NOSE_ANGLE(0.0);

Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_UPPER_MAX_ANGLE(0.0);
Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_UPPER_NOSE_TIGHT(0.5);
Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_UPPER_MAX_TIGHT(0.5);

Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_LOWER_MAX_ANGLE(0.0);
Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_LOWER_NOSE_TIGHT(0.5);
Standard_Real tnbLib::profileLib::NoseCurve_t2::DEFAULT_LOWER_MAX_TIGHT(0.5);

void tnbLib::profileLib::NoseCurve_t2::Perform()
{
	static const Standard_Integer nbPoles = 7;

	Pnt2d P0{ UpperMaxLoc(), UpperMax() };
	Pnt2d P3{ Xo(), Yo() };
	Pnt2d P6{ LowerMaxLoc(),LowerMax() };

	Entity2d_Ray upperRay_3{ P3,{std::sin(NoseAngle()),std::cos(NoseAngle())} };
	Entity2d_Ray ray_0{ P0,{-std::cos(UpperMaxAngle()),-std::sin(UpperMaxAngle())} };

	auto [upperCorner, upperCorner_cond] = Geo_Tools::CalcIntersectionPoint_cgal(upperRay_3, ray_0);
	if (NOT upperCorner_cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to calculate the intersection point." << endl
			<< abort(FatalError);
	}

	auto P1 = Geo_Tools::LinearInterpolate(P0, upperCorner, UpperMaxTight());
	auto P2 = Geo_Tools::LinearInterpolate(P3, upperCorner, UpperNoseTight());

	Entity2d_Ray lowerRay_3{ P3,{-std::sin(NoseAngle()),-std::cos(NoseAngle())} };
	Entity2d_Ray ray_6{ P6,{-std::cos(LowerMaxAngle()), std::sin(LowerMaxAngle())} };

	auto [lowerCorner, lowerCorner_cond] = Geo_Tools::CalcIntersectionPoint_cgal(lowerRay_3, ray_6);
	if (NOT lowerCorner_cond)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to calculate the intersection point." << endl
			<< abort(FatalError);
	}

	auto P4 = Geo_Tools::LinearInterpolate(P3, lowerCorner, LowerNoseTight());
	auto P5 = Geo_Tools::LinearInterpolate(P6, lowerCorner, LowerMaxTight());

	TColgp_Array1OfPnt2d pnts(1, nbPoles);
	pnts.SetValue(1, P0);
	pnts.SetValue(2, P1);
	pnts.SetValue(3, P2);
	pnts.SetValue(4, P3);
	pnts.SetValue(5, P4);
	pnts.SetValue(6, P5);
	pnts.SetValue(7, P6);

	TColStd_Array1OfReal weights(1, nbPoles);
	for (Standard_Integer i = 1; i <= weights.Size(); i++)
	{
		weights.SetValue(i, 1.0);
	}

	TColStd_Array1OfReal knots(1, 3);
	static const auto du = (Standard_Real)0.5;
	knots.SetValue(1, 0);
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
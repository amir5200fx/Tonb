#include <AirfoilPx_GlobalCurve_t1.hxx>

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

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_UPPER_NOSE_TIGHT(0.5);
Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_UPPER_MAX_TIGHT(0.5);

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_UPPER_TRAIL_ANGLE(PI / 6.0);

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_UPPER_MAX_VEL(0.5);
Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_UPPER_TRAIL_VEL(0.5);

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_LOWER_NOSE_TIGHT(0.5);
Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_LOWER_MAX_TIGHT(0.5);

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_LOWER_TRAIL_ANGLE(-PI / 6.0);

Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_LOWER_MAX_VEL(0.5);
Standard_Real tnbLib::profileLib::GlobalCurve_t1::DEFAULT_LOWER_TRAIL_VEL(0.5);

void tnbLib::profileLib::GlobalCurve_t1::Perform()
{
	static const Standard_Integer nbPoles = 13;

	auto max_len = ChordLen() + Xo();
	Pnt2d P0{ max_len,Yo() };
	auto upper_max = Yo() + UpperMax();
	Pnt2d P3{ Geo_Tools::LinearInterpolate(Xo(),max_len,UpperMaxLoc()), upper_max };

	Pnt2d upperTailCorner{ max_len, upper_max };
	auto P2 = Geo_Tools::LinearInterpolate(upperTailCorner, P3, UpperTrailVel());

	Pnt2d P1{ 0, 0 };
	{
		Entity2d_Ray hor_ray{ P2, {1.0, 0.} };
		Entity2d_Ray ver_ray{ P2, {0.0, -1.0} };

		Entity2d_Ray theta_ray{ P0,{-std::cos(UpperTrailAngle()),std::sin(UpperTrailAngle())} };
		auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(ver_ray, theta_ray);
		if (cond)
		{
			P1 = std::move(pt);
		}
		else
		{
			auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(hor_ray, theta_ray);
			if (cond)
			{
				P1 = std::move(pt);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "Something went wrong! cannot find the intersection point" << endl
					<< abort(FatalError);
			}
		}
	}

	Pnt2d P6{ Xo(), Yo() };
	Pnt2d upperNoseCorner;
	{
		Entity2d_Ray ver_ray{ P6,{std::sin(NoseAngle()),std::cos(NoseAngle())} };
		Entity2d_Ray hor_ray{ P3,{-1.0,0.0} };

		auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(hor_ray, ver_ray);
		if (cond)
		{
			upperNoseCorner = std::move(pt);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Something went wrong! couldn't find the intersection point." << endl
				<< abort(FatalError);
		}
	}
	auto P4 = Geo_Tools::LinearInterpolate(P3, upperNoseCorner, UpperMaxTight());
	auto P5 = Geo_Tools::LinearInterpolate(P6, upperNoseCorner, UpperNoseTight());

	auto lower_max = Yo() + LowerMax();
	Pnt2d P9{ Geo_Tools::LinearInterpolate(Xo(),max_len,LowerMaxLoc()),lower_max };

	Pnt2d lowerNoseCorner;
	{
		Entity2d_Ray ver_ray{ P6,{-std::sin(NoseAngle()),-std::cos(NoseAngle())} };
		Entity2d_Ray hor_ray{ P9,{-1.0,0.0} };

		auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(hor_ray, ver_ray);
		if (cond)
		{
			lowerNoseCorner = std::move(pt);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Something went wrong! couldn't find the intersection point." << endl
				<< abort(FatalError);
		}
	}
	auto P7 = Geo_Tools::LinearInterpolate(P6, lowerNoseCorner, LowerNoseTight());
	auto P8 = Geo_Tools::LinearInterpolate(P9, lowerNoseCorner, LowerMaxTight());

	Pnt2d lowerTailCorner{ ChordLen(), lower_max };

	auto P10 = Geo_Tools::LinearInterpolate(lowerTailCorner, P9, LowerMaxVel());
	auto P12 = P0;
	Pnt2d P11{ 0,0 };
	{
		Entity2d_Ray hor_ray{ P10, {1.0, 0.} };
		Entity2d_Ray ver_ray{ P10, {0.0, 1.0} };
		Entity2d_Ray theta_ray{ P12,{-std::cos(LowerTrailAngle()),std::sin(LowerTrailAngle())} };
		auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(ver_ray, theta_ray);
		if (cond)
		{
			P11 = std::move(pt);
		}
		else
		{
			auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(hor_ray, theta_ray);
			if (cond)
			{
				P11 = std::move(pt);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "Something went wrong! cannot find the intersection point" << endl
					<< abort(FatalError);
			}
		}
	}

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
	pnts.SetValue(10, P9);
	pnts.SetValue(11, P10);
	pnts.SetValue(12, P11);
	pnts.SetValue(13, P12);

	TColStd_Array1OfReal weights(1, nbPoles);
	for (Standard_Integer i = 1; i <= weights.Size(); i++)
	{
		weights.SetValue(i, 1.0);
	}

	TColStd_Array1OfReal knots(1, 5);
	static const auto du = (Standard_Real)0.25;
	knots.SetValue(1, 0.0);
	knots.SetValue(2, du);
	knots.SetValue(3, 2*du);
	knots.SetValue(4, 3 * du);
	knots.SetValue(5, 1.0);

	TColStd_Array1OfInteger mults(1, 5);
	mults.SetValue(1, 4);
	mults.SetValue(2, 3);
	mults.SetValue(3, 3);
	mults.SetValue(4, 3);
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
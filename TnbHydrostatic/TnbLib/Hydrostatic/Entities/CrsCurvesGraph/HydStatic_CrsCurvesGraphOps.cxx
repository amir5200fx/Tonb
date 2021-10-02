#include <HydStatic_CrsCurvesGraphOps.hxx>

#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_CrsCurveQ.hxx>
#include <HydStatic_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_TrimmedCurve.hxx>

namespace tnbLib
{

	template<>
	Standard_Real HydStatic_CrsCurvesGraphOps::GetMinDisplv<HydStatic_CrsCurve>
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves
			)
	{
		Standard_Real maxVal = RealFirst();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Dispv0();
			if (f > maxVal)
			{
				maxVal = f;
			}
		}
		return maxVal;
	}

	template<>
	Standard_Real HydStatic_CrsCurvesGraphOps::GetMaxDisplv<HydStatic_CrsCurve>
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves
			)
	{
		Standard_Real minVal = RealLast();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Dispv1();
			if (f < minVal)
			{
				minVal = f;
			}
		}
		return minVal;
	}

	template<>
	Standard_Real HydStatic_CrsCurvesGraphOps::GetMinDisplv<HydStatic_CrsCurveQ>
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>& theCurves
			)
	{
		Standard_Real maxVal = RealFirst();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Dispv0();
			if (f > maxVal)
			{
				maxVal = f;
			}
		}
		return maxVal;
	}

	template<>
	Standard_Real HydStatic_CrsCurvesGraphOps::GetMaxDisplv<HydStatic_CrsCurveQ>
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>& theCurves
			)
	{
		Standard_Real minVal = RealLast();
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto f = x->Dispv1();
			if (f < minVal)
			{
				minVal = f;
			}
		}
		return minVal;
	}

	Handle(Geom2d_Curve) ClipCurve
	(
		const Handle(Geom2d_Curve)& theGeom,
		const Standard_Real u0,
		const Standard_Real u1
	)
	{
		const auto du = u1 - u0;
		Handle(Geom2d_TrimmedCurve) cliped = new Geom2d_TrimmedCurve(theGeom, u0 + 1.0E-6*du, u1 - 1.0E-6*du);
		return std::move(cliped);
	}

	template<>
	std::shared_ptr<HydStatic_CrsCurve> HydStatic_CrsCurvesGraphOps::ClipCurve<HydStatic_CrsCurve>
		(
			const std::shared_ptr<HydStatic_CrsCurve>& theCurve,
			const Standard_Real x0, 
			const Standard_Real x1, 
			const hydStcLib::CurveMakerType t
			)
	{
		const auto id = theCurve->Index();
		const auto& name = theCurve->Name();

		auto t0 = theCurve->ValueP(x0);
		auto t1 = theCurve->ValueP(x1);

		auto geom = ::tnbLib::ClipCurve(theCurve->Geometry(), t0.second, t1.second);
		auto curve = hydStcLib::MakeCurve<HydStatic_CrsCurve>(std::move(geom), t);

		curve->SetIndex(id);
		curve->SetName(name);

		curve->SetHeel(theCurve->Heel());
		return std::move(curve);
	}

	template<>
	std::shared_ptr<HydStatic_CrsCurveQ> HydStatic_CrsCurvesGraphOps::ClipCurve<HydStatic_CrsCurveQ>
		(
			const std::shared_ptr<HydStatic_CrsCurveQ>& theCurve,
			const Standard_Real x0, 
			const Standard_Real x1, 
			const hydStcLib::CurveMakerType t
			)
	{
		const auto id = theCurve->Index();
		const auto& name = theCurve->Name();

		auto curve = HydStatic_Tools::Trim(theCurve, x0, x1, t, 1.0E-20);

		curve->SetIndex(id);
		curve->SetName(name);

		curve->SetHeel(theCurve->Heel());
		return std::move(curve);
	}
}
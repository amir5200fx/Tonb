#include <HydStatic_CrsCurvesGraph.hxx>

#include <HydStatic_CrsCurve.hxx>

#include <Standard_Real.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Curve.hxx>

tnbLib::HydStatic_CrsCurvesGraph::HydStatic_CrsCurvesGraph
(
	const Standard_Integer theIndex,
	const word & theName
)
	: HydStatic_Entity(theIndex, theName)
{
	// empty body
}

namespace tnbLib
{

	hydStcLib::CurveMakerType GetType(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves)
	{
		Debug_If_Condition(theCurves.empty());
		const auto t = hydStcLib::RetrieveType(theCurves[0]);
#ifdef _DEBUG
		for (const auto& x : theCurves)
		{
			if (hydStcLib::RetrieveType(x) NOT_EQUAL t)
			{
				FatalErrorIn(FunctionSIG)
					<< "the type of the curves must be the same" << endl
					<< abort(FatalError);
			}
		}
#endif // _DEBUG
		return t;
	}

	Standard_Real GetMinDisplv(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves)
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

	Standard_Real GetMaxDisplv(const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves)
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
		Handle(Geom2d_TrimmedCurve) cliped = new Geom2d_TrimmedCurve(theGeom, u0, u1);
		return std::move(cliped);
	}

	std::shared_ptr<HydStatic_CrsCurve> ClipCurve
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

		auto geom = ClipCurve(theCurve->Geometry(), t0.second, t1.second);
		auto curve = hydStcLib::MakeCurve<HydStatic_CrsCurve>(std::move(geom), t);
		return std::move(curve);
	}
}

void tnbLib::HydStatic_CrsCurvesGraph::Perform
(
	const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves
)
{
	const auto x0 = GetMinDisplv(theCurves);
	const auto x1 = GetMaxDisplv(theCurves);
	const auto t = GetType(theCurves);

	auto& curves = theCurves_;
	curves.reserve(theCurves.size());
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		auto c = ClipCurve(x, x0, x1, t);
		curves.push_back(std::move(c));
	}
	Change_IsDone() = Standard_True;
}
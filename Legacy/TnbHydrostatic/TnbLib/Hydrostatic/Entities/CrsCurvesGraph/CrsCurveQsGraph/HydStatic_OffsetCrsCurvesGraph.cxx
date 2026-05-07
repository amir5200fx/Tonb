#include <HydStatic_OffsetCrsCurvesGraph.hxx>

#include <HydStatic_CrsCurveQ.hxx>
#include <HydStatic_CrsCurvesGraphOps.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::HydStatic_OffsetCrsCurvesGraph::Perform()
{
	if (Curves().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto x0 = HydStatic_CrsCurvesGraphOps::GetMinDisplv(Curves());
	const auto x1 = HydStatic_CrsCurvesGraphOps::GetMaxDisplv(Curves());

	const auto t = hydStcLib::RetrieveTypeQ(Curves());

	std::vector<std::shared_ptr<HydStatic_CrsCurveQ>> curves;
	curves.reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		auto c = HydStatic_CrsCurvesGraphOps::ClipCurve(x, x0, x1, t);
		curves.push_back(std::move(c));
	}

	const auto& c = curves[0];
	Debug_Null_Pointer(c);

	SetMinDispv(c->LowerDispv());
	SetMaxDispv(c->UpperDispv());

	theCurves_ = std::move(curves);

	Change_IsDone() = Standard_True;
}

Standard_Integer 
tnbLib::HydStatic_OffsetCrsCurvesGraph::NbCurves() const
{
	return (Standard_Integer)theCurves_.size();
}

tnbLib::hydStcLib::CurveMakerType 
tnbLib::HydStatic_OffsetCrsCurvesGraph::CurveType() const
{
	CheckIsDone();
	return hydStcLib::RetrieveTypeQ(Curves());
}

std::vector
<
	std::pair
	<
	tnbLib::HydStatic_CrsCurvesGraph::LeverArm,
	tnbLib::HydStatic_CrsCurvesGraph::Heel
	>
>
tnbLib::HydStatic_OffsetCrsCurvesGraph::RetrieveLeverArms
(
	const Standard_Real vol
) const
{
	CheckVolume(vol);

	std::vector<std::pair<LeverArm, Heel>> values;
	values.reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);

		auto lever = LeverArm{ x->LeverArm(vol) };
		auto heel = Heel{ x->Heel() };

		auto paired = std::make_pair(std::move(lever), std::move(heel));
		values.push_back(std::move(paired));
	}
	return std::move(values);
}

void tnbLib::HydStatic_OffsetCrsCurvesGraph::Perform
(
	const std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>& theCurves
)
{
	theCurves_ = theCurves;
	Perform();
}

void tnbLib::HydStatic_OffsetCrsCurvesGraph::Perform
(
	std::vector<std::shared_ptr<HydStatic_CrsCurveQ>>&& theCurves
)
{
	theCurves_ = std::move(theCurves);
	Perform();
}
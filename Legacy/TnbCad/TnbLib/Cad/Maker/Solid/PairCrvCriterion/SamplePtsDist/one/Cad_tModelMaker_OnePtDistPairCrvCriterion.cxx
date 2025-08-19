#include <Cad_tModelMaker_OnePtDistPairCrvCriterion.hxx>

#include <Cad_CurveSplitter.hxx>
#include <Cad_Tools.hxx>
#include <TModel_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Curve.hxx>

namespace tnbLib
{
	namespace crvCriterion
	{

		static const Standard_Integer OnePtDistPairCrvCriterionNbSamples = 15;

		static auto GetSamplePoint
		(
			const Handle(Geom_Curve)& theGeometry,
			const std::shared_ptr<Cad_CurveSplitter_Info>& theInfo
		)
		{
			auto splitterAlg = std::make_shared<Cad_CurveSplitter>(theGeometry, OnePtDistPairCrvCriterionNbSamples - 1, theInfo);
			Debug_Null_Pointer(splitterAlg);

			splitterAlg->Perform();
			Debug_If_Condition_Message(NOT splitterAlg->IsDone(), "the applicatiuon is not performed!");

			const auto& params = splitterAlg->ResultsPrameters();
			Debug_If_Condition((Standard_Integer)params.size() NOT_EQUAL OnePtDistPairCrvCriterionNbSamples);

			const auto p = params[OnePtDistPairCrvCriterionNbSamples / 2];
			Pnt3d pt = theGeometry->Value(p);
			return std::move(pt);
		}
	}
}

Standard_Boolean 
tnbLib::cadLib::tModelMaker_OnePtDistPairCrvCriterion::ArePaired
(
	const std::shared_ptr<TModel_Curve>& theCurve0,
	const std::shared_ptr<TModel_Curve>& theCurve1
) const
{
	Debug_Null_Pointer(theCurve0);
	Debug_Null_Pointer(theCurve1);

	const auto& g0 = theCurve0->Geometry();
	const auto& g1 = theCurve1->Geometry();

	const auto crvLen0 = Cad_Tools::CalcLength(g0, CurveLengthInfo());
	const auto crvLen1 = Cad_Tools::CalcLength(g1, CurveLengthInfo());
	
	if (std::abs(crvLen0 - crvLen1) < Tolerance())
	{
		const auto pt0 = crvCriterion::GetSamplePoint(g0, CurveSplitterInfo());
		const auto pt1 = crvCriterion::GetSamplePoint(g1, CurveSplitterInfo());
		
		if (pt0.Distance(pt1) <= Tolerance())
		{
			return Standard_True;
		}
	}
	return Standard_False;
}
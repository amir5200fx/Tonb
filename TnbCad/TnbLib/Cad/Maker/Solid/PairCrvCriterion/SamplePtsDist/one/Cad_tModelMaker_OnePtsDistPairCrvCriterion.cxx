#include <Cad_tModelMaker_OnePtsDistPairCrvCriterion.hxx>

#include <Cad_Tools.hxx>
#include <TModel_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>



Standard_Boolean 
tnbLib::cadLib::tModelMaker_OnePtsDistPairCrvCriterion::ArePaired
(
	const std::shared_ptr<TModel_Curve>& theCurve0,
	const std::shared_ptr<TModel_Curve>& theCurve1
) const
{
	Debug_Null_Pointer(theCurve0);
	Debug_Null_Pointer(theCurve1);

	const auto& g0 = theCurve0->Geometry();
	const auto& g1 = theCurve1->Geometry();

	const auto crvLen0 = Cad_Tools::CalcLength(g0, IntegInfo());
	const auto crvLen1 = Cad_Tools::CalcLength(g1, IntegInfo());

	if (std::abs(crvLen0 - crvLen1) < Tolerance())
	{

	}
	else
	{
		return Standard_False;
	}
}
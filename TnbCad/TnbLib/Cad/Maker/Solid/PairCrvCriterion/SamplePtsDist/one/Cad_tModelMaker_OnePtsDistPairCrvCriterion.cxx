#include <Cad_tModelMaker_OnePtsDistPairCrvCriterion.hxx>

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


}
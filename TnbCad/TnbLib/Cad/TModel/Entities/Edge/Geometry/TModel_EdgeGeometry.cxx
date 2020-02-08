#include <TModel_EdgeGeometry.hxx>

#include <TModel_Curve.hxx>
#include <Geo3d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>

#include <Geom_Curve.hxx>

void tnbLib::TModel_EdgeGeometry::Discrete
(
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
) const
{
	if (NOT Curve())
		return;

	const auto& curve = Curve();

	auto alg = std::make_shared<Geo3d_ApprxCurve>();
	Debug_Null_Pointer(alg);

	alg->LoadCurve(curve->Geometry(), curve->FirstParameter(), 
		curve->LastParameter(), theInfo);

	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

	ChangeMesh() = alg->Chain();
}
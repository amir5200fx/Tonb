#include <Aft2d_PlnCurveUniMetric.hxx>

#include <Aft2d_SegmentEdgeUniMetric.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <Mesh2d_CurveUniMetric.hxx>

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdgeUniMetric>>
tnbLib::Aft2d_PlnCurveUniMetric::TopoMesh<tnbLib::Aft2d_SegmentEdgeUniMetric>
(
	const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto chain = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(chain);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_SegmentEdgeUniMetric::GetTopology(*chain, theCurve);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& P0 = x->Node0()->Coord();
		const auto& P1 = x->Node1()->Coord();

		x->SetCharLength(theCurve->CalcCharLength(P0, P1, theMap));
		x->SetCentre(theCurve->CalcCentre(P0, P1, theMap));
	}
	return std::move(edges);
}
#include <Aft2d_gPlnCurveSurface.hxx>

#include <Aft2d_gSegmentEdge.hxx>
#include <error.hxx>
#include <OSstream.hxx>

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdge>>
tnbLib::Aft2d_gPlnCurveSurface::TopoMesh<tnbLib::Aft2d_gSegmentEdge>
(
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto chain = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(chain);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_gSegmentEdge::GetTopology(*chain, theCurve);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& P0 = x->Node0()->Coord();
		const auto& P1 = x->Node1()->Coord();

		x->SetCharLength(sizeMap.CalcDistance(P0, P1));
		x->SetCentre(sizeMap.CalcCentre(P0, P1));
	}
	return std::move(edges);
}
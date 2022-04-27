#include <Cad_gPoleSingularCurve.hxx>

#include <Aft2d_gSegmentPoleEdge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdge>> 
tnbLib::Cad_gPoleSingularCurve::TopoMesh<tnbLib::Aft2d_gSegmentEdge>
(
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto poly = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(poly);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_gSegmentPoleEdge::GetTopology(*poly, theCurve);

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
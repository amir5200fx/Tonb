#include <Cad2d_PlnGapCurveUniMetric.hxx>

#include <Aft2d_SegmentEdgeUniMetric.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_PlnCurveUniMetric>,
	std::shared_ptr<tnbLib::Aft2d_PlnCurveUniMetric>
>
tnbLib::Cad2d_PlnGapCurveUniMetric::Split(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto [c0, c1] = Curve()->Split(x);
	if (NOT c0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	if (NOT c1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	auto C0 = std::make_shared<Cad2d_PlnGapCurveUniMetric>(std::move(c0));
	auto C1 = std::make_shared<Cad2d_PlnGapCurveUniMetric>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdgeUniMetric>>
tnbLib::Cad2d_PlnGapCurveUniMetric::TopoMesh<tnbLib::Aft2d_SegmentEdgeUniMetric>
(
	const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto poly = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(poly);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_SegmentEdgeUniMetric::GetTopology(*poly, theCurve);

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
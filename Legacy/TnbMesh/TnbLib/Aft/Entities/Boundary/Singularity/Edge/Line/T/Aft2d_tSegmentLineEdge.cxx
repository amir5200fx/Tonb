#include <Aft2d_tSegmentLineEdge.hxx>

#include <Aft2d_tCornerLineNode.hxx>
#include <Aft2d_tSegmentLineNode.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Entity2d_Polygon.hxx>

template<>
Standard_Boolean tnbLib::Aft2d_tSegmentLineEdge::SingularityContraction(const Geo2d_MetricPrcsrAnIso& thePrcsr)
{
	return Standard_False;
}

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Aft2d_tSegmentLineEdge::GetTopology
(
	const Entity2d_Polygon& theChain,
	const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve
)
{
	const auto& pts = theChain.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid chain: a valid chain must have more than 2 points" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes;
	nodes.reserve(pts.size());

	Standard_Integer K = 0;
	K++;
	auto n0 = std::make_shared<Aft2d_tCornerLineNode>(K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		K++;
		auto n = std::make_shared<Aft2d_tSegmentLineNode>(K, pts[K - 1]);
		Debug_Null_Pointer(n);

		n->SetCurve(theCurve);

		nodes.push_back(std::move(n));
	}

	K++;
	auto n1 = std::make_shared<Aft2d_tCornerLineNode>(K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_tSegmentEdge>> edges;
	edges.reserve(pts.size() - 1);

	K = 0;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes[i - 1];
		const auto& n1 = nodes[i];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_tSegmentLineEdge>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}
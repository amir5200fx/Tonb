#include <Geo2d_KnitChain.hxx>

#include <Knit_ChainNode.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_PolygonSegmentGraphEdge.hxx>
#include <Geo2d_PolygonRingGraphEdge.hxx>
#include <Geo2d_PolygonGraphNode.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	std::pair<std::shared_ptr<Geo2d_PolygonGraphNode>, std::shared_ptr<Geo2d_PolygonGraphNode>>
		CreateNodes(const std::shared_ptr<Entity2d_Polygon>& thePoly)
	{
		const auto& points = thePoly->Points();
		if (points.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid chain has been detected!" << endl
				<< abort(FatalError);
		}

		const auto& p0 = points[0];
		const auto& p1 = points[points.size() - 1];

		auto n0 = std::make_shared<Geo2d_PolygonGraphNode>(0, p0);
		auto n1 = std::make_shared<Geo2d_PolygonGraphNode>(1, p1);
		auto t = std::make_pair(std::move(n0), std::move(n1));
		return std::move(t);
	}

	std::shared_ptr<Geo2d_PolygonGraphNode> 
		CreateRingNode(const std::shared_ptr<Entity2d_Polygon>& thePoly)
	{
		const auto& points = thePoly->Points();
		if (points.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid chain has been detected!" << endl
				<< abort(FatalError);
		}

		const auto& p0 = points[0];

		auto n = std::make_shared<Geo2d_PolygonGraphNode>(0, p0);
		return std::move(n);
	}
}

template<>
void tnbLib::Geo2d_KnitChain::Perform()
{
	// creating regular chains [1/5/2022 Amir]
	auto start = FindStart(Knit_ChainNode_Type::start);

	Standard_Integer nbEdges = 0;
	while (start)
	{
		auto poly = GetPolygon(start);
		auto[n0, n1] = CreateNodes(poly);

		auto edge = std::make_shared<Geo2d_PolygonSegmentGraphEdge>
			(++nbEdges, std::move(n0), std::move(n1));
		Debug_Null_Pointer(edge);

		edge->SetPolygon(std::move(poly));

		n0->InsertToEdges(edge->Index(), edge);
		n1->InsertToEdges(edge->Index(), edge);

		start = FindStart(Knit_ChainNode_Type::start);
	}

	// creating ring chains [1/5/2022 Amir]
	Standard_Integer nbRings = 0;
	if (NbEdges())
	{
		start = FindStart(Knit_ChainNode_Type::regular);
		while (start)
		{
			auto poly = GetPolygon(start);
			auto n = CreateRingNode(poly);

			auto edge = std::make_shared<Geo2d_PolygonRingGraphEdge>
				(++nbRings, std::move(n));
			Debug_Null_Pointer(edge);

			edge->SetPolygon(std::move(poly));

			n->InsertToEdges(edge->Index(), edge);

			start = FindStart(Knit_ChainNode_Type::regular);
		}
	}

	if (NbNodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "the node tree is not empty." << endl
			<< " - something went wrong!" << endl
			<< abort(FatalError);
	}

	if (NbEdges())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge tree is not empty." << endl
			<< " - something went wrong!" << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}
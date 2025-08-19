#include <Geo_GraphTools.hxx>

#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_RingGraphEdge.hxx>
#include <Geo2d_GraphNode.hxx>
#include <Geo2d_Graph.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Tools.hxx>
#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::pair<Standard_Boolean, std::shared_ptr<tnbLib::Geo2d_GraphEdge>>
tnbLib::Geo_GraphTools::IsEdge
(
	const std::shared_ptr<Geo2d_GraphNode>& theNode0,
	const std::shared_ptr<Geo2d_GraphNode>& theNode1
)
{
	if (NOT theNode0->NbEdges())
	{
		std::shared_ptr<tnbLib::Geo2d_GraphEdge> e;
		auto t = std::make_pair(Standard_False, e);
		return std::move(t);
	}
	if (theNode0->NbEdges() > theNode1->NbEdges())
	{
		return IsEdge(theNode1, theNode0);
	}
	else
	{
		const auto& edges = theNode0->Edges();
		for (const auto& x : edges)
		{
			auto e = x.second.lock();
			Debug_Null_Pointer(e);

			auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(e);
			if (NOT seg)
			{
				FatalErrorIn(FunctionSIG)
					<< "the link is not a segment." << endl
					<< abort(FatalError);
			}

			if (seg->Node0() IS_EQUAL theNode1)
			{
				auto t = std::make_pair(Standard_True, std::move(e));
				return std::move(t);
			}

			if (seg->Node1() IS_EQUAL theNode1)
			{
				auto t = std::make_pair(Standard_True, std::move(e));
				return std::move(t);
			}
		}
	}
	std::shared_ptr<tnbLib::Geo2d_GraphEdge> e;
	auto t = std::make_pair(Standard_False, e);
	return std::move(t);
}

std::vector<std::shared_ptr<tnbLib::Geo2d_GraphNode>> 
tnbLib::Geo_GraphTools::GetNodes(const std::vector<Pnt2d>& thePts)
{
	std::vector<std::shared_ptr<Geo2d_GraphNode>> nodes;
	nodes.reserve(thePts.size());

	Standard_Integer k = 0;
	for (const auto& x : thePts)
	{
		auto node = std::make_shared<Geo2d_GraphNode>(++k, x);
		nodes.push_back(std::move(node));
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Geo2d_GraphEdge>> 
tnbLib::Geo_GraphTools::GetEdges
(
	const std::vector<std::shared_ptr<Geo2d_GraphNode>>& theNodes,
	const std::vector<connectivity::triple>& theIds
)
{
	Standard_Integer k = 0;

	std::vector<std::shared_ptr<Geo2d_GraphEdge>> edges;
	for (const auto& x : theIds)
	{
		auto v0 = x.Value(0);
		auto v1 = x.Value(1);
		auto v2 = x.Value(2);

		{
			const auto& n0 = theNodes.at(Index_Of(v0));
			const auto& n1 = theNodes.at(Index_Of(v1));
			
			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto[isEdge, edge] = IsEdge(n0, n1);

			if (NOT isEdge)
			{
				auto newEdge = std::make_shared<Geo2d_SegmentGraphEdge>(++k, n0, n1);			

				n0->InsertToEdges(newEdge->Index(), newEdge);
				n1->InsertToEdges(newEdge->Index(), newEdge);

				edges.push_back(std::move(newEdge));
			}
		}

		{
			const auto& n0 = theNodes.at(Index_Of(v1));
			const auto& n1 = theNodes.at(Index_Of(v2));

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto[isEdge, edge] = IsEdge(n0, n1);

			if (NOT isEdge)
			{
				auto newEdge = std::make_shared<Geo2d_SegmentGraphEdge>(++k, n0, n1);		

				n0->InsertToEdges(newEdge->Index(), newEdge);
				n1->InsertToEdges(newEdge->Index(), newEdge);

				edges.push_back(std::move(newEdge));
			}
		}

		{
			const auto& n0 = theNodes.at(Index_Of(v2));
			const auto& n1 = theNodes.at(Index_Of(v0));

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto[isEdge, edge] = IsEdge(n0, n1);

			if (NOT isEdge)
			{
				auto newEdge = std::make_shared<Geo2d_SegmentGraphEdge>(++k, n0, n1);
				
				n0->InsertToEdges(newEdge->Index(), newEdge);
				n1->InsertToEdges(newEdge->Index(), newEdge);

				edges.push_back(std::move(newEdge));
			}
		}
	}
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::Geo2d_GraphEdge>>
tnbLib::Geo_GraphTools::GetEdges
(
	const std::vector<std::shared_ptr<Geo2d_GraphNode>>& theNodes, 
	const std::vector<connectivity::dual>& theIds
)
{
	Standard_Integer k = 0;

	std::vector<std::shared_ptr<Geo2d_GraphEdge>> edges;
	for (const auto& x : theIds)
	{
		const auto v0 = x.Value(0);
		const auto v1 = x.Value(1);

		const auto& n0 = theNodes.at(Index_Of(v0));
		const auto& n1 = theNodes.at(Index_Of(v1));

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto [isEdge, edge] = IsEdge(n0, n1);

		if (NOT isEdge)
		{
			auto newEdge = std::make_shared<Geo2d_SegmentGraphEdge>(++k, n0, n1);

			n0->InsertToEdges(newEdge->Index(), newEdge);
			n1->InsertToEdges(newEdge->Index(), newEdge);

			edges.push_back(std::move(newEdge));
		}
	}
	return std::move(edges);
}

std::shared_ptr<tnbLib::Geo2d_Graph> 
tnbLib::Geo_GraphTools::GetGraph
(
	const Entity2d_Triangulation & theTri
)
{
	const auto nodes = GetNodes(theTri.Points());
	const auto edges = GetEdges(nodes, theTri.Connectivity());

	auto g = std::make_shared<Geo2d_Graph>();
	Debug_Null_Pointer(g);

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		g->Insert(x->Index(), std::move(x));
	}
	return std::move(g);
}

std::shared_ptr<tnbLib::Geo2d_Graph>
tnbLib::Geo_GraphTools::GetGraph
(
	const Entity2d_Polygon& thePolygon
)
{
	std::vector<Pnt2d> pts;
	if (thePolygon.IsClosed())
	{
		const auto& points = thePolygon.Points();
		for (size_t i = 0; i < points.size() - 1; i++)
		{
			pts.emplace_back(points.at(i));
		}
	}
	else
	{
		pts = thePolygon.Points();
	}
	std::shared_ptr<Entity2d_Chain> chain;
	if (thePolygon.IsClosed())
	{
		chain = Geo_Tools::RetrieveClosedChain(thePolygon);
	}
	else
	{
		chain = Geo_Tools::RetrieveChain(thePolygon);
	}
	const auto nodes = GetNodes(thePolygon.Points());
	const auto edges = GetEdges(nodes, chain->Connectivity());

	auto g = std::make_shared<Geo2d_Graph>();
	Debug_Null_Pointer(g);

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		g->Insert(x->Index(), std::move(x));
	}
	return std::move(g);
}

std::vector<std::shared_ptr<tnbLib::Geo2d_GraphNode>> 
tnbLib::Geo_GraphTools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Geo2d_GraphEdge>>& theEdges
)
{
	std::map<Standard_Integer, std::shared_ptr<Geo2d_GraphNode>> nodeMap;
	for (const auto& x : theEdges)
	{
		if (auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(x))
		{
			const auto& n0 = seg->Node0();
			const auto& n1 = seg->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			Global_Tools::InsertIgnoreDup(n0->Index(), n0, nodeMap);
			Global_Tools::InsertIgnoreDup(n1->Index(), n1, nodeMap);
		}
		else if (auto ring = std::dynamic_pointer_cast<Geo2d_RingGraphEdge>(x))
		{
			const auto& n = ring->Node();

			Debug_Null_Pointer(n);

			Global_Tools::InsertIgnoreDup(n->Index(), n, nodeMap);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of edge has been detected!" << endl
				<< abort(FatalError);
		}
	}
	auto nodes = Global_Tools::RetrieveValuesToList(nodeMap);
	return std::move(nodes);
}

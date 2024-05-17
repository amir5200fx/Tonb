#include <Aft3d_Volume.hxx>

#include <Aft3d_FaceNode.hxx>
#include <Aft3d_FaceEdge.hxx>
#include <Aft3d_BoundaryFacet.hxx>
#include <Entity3d_TopoTriangulation.hxx>

namespace tnbLib
{
	namespace createBoundary
	{
		auto find_apex(const std::shared_ptr<legLib::Aft3d_Edge>& edge, const std::shared_ptr<legLib::Aft3d_Facet>& facet)
		{
			std::set<std::shared_ptr<legLib::Aft3d_Node>, decltype(legLib::node_comp)> comp(legLib::node_comp);
			comp.insert(facet->Node0());
			comp.insert(facet->Node1());
			comp.insert(facet->Node2());
			const auto& v0 = edge->Node0();
			const auto& v1 = edge->Node1();
			if (const auto iter = comp.find(v0); iter NOT_EQUAL comp.end())
			{
				comp.erase(iter);
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " the edge doesn't belong to the facet" << endl
					<< abort(FatalError);
			}
			if (const auto iter = comp.find(v1); iter NOT_EQUAL comp.end())
			{
				comp.erase(iter);
			}
			else
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " the edge doesn't belong to the facet" << endl
					<< abort(FatalError);
			}
			return *comp.begin();
		}
	}
}

void tnbLib::legLib::Aft3d_Volume::CreateBoundary(const Entity3d_TopoTriangulation& theTriangulation)
{
	// Creating the nodes
	std::vector<std::shared_ptr<Aft3d_FaceNode>> nodes;
	nodes.reserve(theTriangulation.NbPoints());
	Standard_Integer nb_nodes = 0;
	for (const auto& pt : theTriangulation.Points())
	{
		auto node = std::make_shared<Aft3d_FaceNode>(++nb_nodes, pt);
		nodes.emplace_back(std::move(node));
	}
	// Creating the edges
	std::vector<std::shared_ptr<Aft3d_FaceEdge>> edges;
	edges.reserve(theTriangulation.NbSegments());
	Standard_Integer nb_edges = 0;
	for (const auto& seg: theTriangulation.Segments())
	{
		const auto v0 = seg.Value(0);
		const auto v1 = seg.Value(1);
		const auto& node0 = nodes.at(Index_Of(v0));
		const auto& node1 = nodes.at(Index_Of(v1));
		auto edge = std::make_shared<Aft3d_FaceEdge>(++nb_edges, Aft3d_FaceEdge::Array2{node0, node1});
		edges.emplace_back(std::move(edge));

		// connecting the nodes and the edge
		node0->InsertEdge(edge);
		node1->InsertEdge(edge);
	}
	// Creating the facets
	std::vector<std::shared_ptr<Aft3d_Facet>> facets;
	facets.reserve(theTriangulation.NbConnectivity());
	Standard_Integer nb_facets = 0;
	for (const auto& f: theTriangulation.Connectivity())
	{
		const auto v0 = f.Value(0);
		const auto v1 = f.Value(1);
		const auto v2 = f.Value(2);
		const auto& n0 = nodes.at(Index_Of(v0));
		const auto& n1 = nodes.at(Index_Of(v1));
		const auto& n2 = nodes.at(Index_Of(v2));
		auto facet = std::make_shared<Aft3d_BoundaryFacet>(++nb_facets, Aft3d_Facet::NodeArray3{n0, n1, n2});
		facets.emplace_back(std::move(facet));

		// connecting the nodes and the face
		n0->InsertFacet(facet);
		n1->InsertFacet(facet);
		n2->InsertFacet(facet);
	}
	// connecting the edges to the facets
	const auto& segments = theTriangulation.Segments();
	for (const auto& edge: edges)
	{
		const auto id = edge->Index();
		const auto& seg = segments.at(Index_Of(id));
		{
			const auto id = seg.Value(0);
			if (NOT id)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "the boundary mesh is not closed." << endl
					<< abort(FatalError);
			}
			const auto& facet = facets.at(Index_Of(id));
			auto apex = createBoundary::find_apex(edge, facet);

			facet->SetEdge(facet->FindNodeId(apex), edge);
			edge->InsertFacet(facet);
		}
		{
			const auto id = seg.Value(1);
			if (NOT id)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "the boundary mesh is not closed." << endl
					<< abort(FatalError);
			}
			const auto& facet = facets.at(Index_Of(id));
			const auto apex = createBoundary::find_apex(edge, facet);

			facet->SetEdge(facet->FindNodeId(apex), edge);
			edge->InsertFacet(facet);
		}
	}
	theBoundary_ = 
		std::make_shared<std::vector<std::shared_ptr<Aft3d_Facet>>>
	(std::move(facets));
}

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
	std::cout << "creating the nodes...\n";
	// Creating the nodes
	std::vector<std::shared_ptr<Aft3d_FaceNode>> nodes;
	nodes.reserve(theTriangulation.NbPoints());
	Standard_Integer nb_nodes = 0;
	for (const auto& pt : theTriangulation.Points())
	{
		auto node = std::make_shared<Aft3d_FaceNode>(++nb_nodes, pt);
		nodes.emplace_back(std::move(node));
	}
	std::cout << "nb of nodes = " << nodes.size() << "\n";
	std::cout << "creating the edges...\n";
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
		// connecting the nodes and the edge
		Debug_Null_Pointer(node0);
		node0->InsertEdge(edge);
		Debug_Null_Pointer(node1);
		node1->InsertEdge(edge);
		// Putting the edge into the array
		edges.emplace_back(std::move(edge));
	}
	std::cout << "creating the facets...\n";
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
		// connecting the nodes and the face
		n0->InsertFacet(facet);
		n1->InsertFacet(facet);
		n2->InsertFacet(facet);
		// Putting the facet into the array
		facets.emplace_back(std::move(facet));
	}
	std::cout << "connecting the edges and the facets...\n";
	// connecting the edges to the facets
	const auto& tas = theTriangulation.TAS();
	const auto& segments = theTriangulation.Segments();
	for (size_t i = 0; i < tas.size(); i++)
	{
		const auto e0 = tas.at(i).Value(0);
		const auto e1 = tas.at(i).Value(1);
		std::cout << "e0 = " << e0 << ", e1 = " << e1 << "\n";
		const auto& edge = edges.at(i);
		if (e0)
		{
			const auto& facet = facets.at(Index_Of(e0));
			auto apex = createBoundary::find_apex(edge, facet);
			
			facet->SetEdge(facet->FindNodeId(apex), edge);
			edge->InsertFacet(facet);
		}
		if (e1)
		{
			const auto& facet = facets.at(Index_Of(e1));
			auto apex = createBoundary::find_apex(edge, facet);

			facet->SetEdge(facet->FindNodeId(apex), edge);
			edge->InsertFacet(facet);
		}
	}
	/*for (const auto& edge: edges)
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
	}*/
	theBoundary_ = 
		std::make_shared<std::vector<std::shared_ptr<Aft3d_Facet>>>
	(std::move(facets));
}

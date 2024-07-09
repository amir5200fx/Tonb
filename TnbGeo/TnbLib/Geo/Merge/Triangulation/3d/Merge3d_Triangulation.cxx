#include <Extrema_POnCurv2d.hxx>
#include <Merge3d_Triangulation.hxx>

#include <Geo3d_BalPrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Pnt3d.hxx>
#include <Global_Indexed.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>
#include <set>

#include "Entity_StaticData.hxx"

namespace tnbLib
{
	namespace geoLib
	{
		namespace mergeTris3d
		{
			// Forward Declarations
			class Edge;
			class Node;

			struct SuperNode
			{
				Standard_Integer id;
				Pnt3d coord;

				std::vector<std::shared_ptr<Node>> nodes;

				Standard_Integer MinId() const;

				typedef Pnt3d ptType;
			};

			class NodeAdaptor
			{
				/*Private Data*/
				std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;
				std::weak_ptr<SuperNode> theSuperNode_;
			protected:
				// default constructor
				NodeAdaptor() = default;
			public:
				// Public functions and operators
				Standard_Integer NbEdges() const { return static_cast<Standard_Integer>(theEdges_.size()); }
				const auto& Edges() const { return theEdges_; }
				const auto& Super() const { return theSuperNode_; }

				void InsertToEdges(const Standard_Integer theIndex, const std::weak_ptr<Edge>&);
				void SetSuper(const std::shared_ptr<SuperNode>& node) { theSuperNode_ = node; }
			};

			void NodeAdaptor::InsertToEdges(const Standard_Integer theIndex, const std::weak_ptr<Edge>& theEdge)
			{
				if (!theEdges_.insert({theIndex, theEdge}).second)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "duplicate data." << endl
						<< " - index: " << theIndex << endl
						<< abort(FatalError);
				}
			}

			class Node
				: public NodeAdaptor
				, public Global_Indexed
			{
				/*Private Data*/
				Pnt3d theCoord_;
			public:
				typedef Pnt3d ptType;
				// default constructor
				Node() = default;
				// constructors
				Node(const Standard_Integer theIndex, const Pnt3d& theCoord)
					: Global_Indexed(theIndex)
					, theCoord_(theCoord)
				{}
				Node(const Standard_Integer theIndex, Pnt3d&& theCoord)
					: Global_Indexed(theIndex)
					, theCoord_(std::move(theCoord))
				{}
				// Public functions and operators
				const auto& Coord() const { return theCoord_; }

				void SetCoord(const Pnt3d& theCoord) { theCoord_ = theCoord; }
				void SetCoord(Pnt3d&& theCoord) { theCoord_ = std::move(theCoord); }
			};

			Standard_Integer SuperNode::MinId() const
			{
				Standard_Integer min_id = IntegerLast();
				std::for_each(nodes.begin(), nodes.end(), [&min_id](const std::shared_ptr<Node>& node)
					{
						if (node->Index() < min_id)
						{
							min_id = node->Index();
						}
					});
				return min_id;
			}

			auto compare_nodes = [](const std::shared_ptr<Node>& node0, const std::shared_ptr<Node>& node1)
			{
				return node0->Index() < node1->Index();
			};

			class EdgeAdaptor
			{
				/*Private Data*/
				std::map<Standard_Integer, std::weak_ptr<Edge>> thePairs_;
			protected:
				// default constructor
				EdgeAdaptor() = default;
			public:
				// Public functions and operators
				Standard_Integer NbPairs() const { return static_cast<Standard_Integer>(thePairs_.size()); }
				const auto& Pairs() const { return thePairs_; }

				void InsertToPairs(const Standard_Integer theIndex, const std::shared_ptr<Edge>& edge);
			};

			void EdgeAdaptor::InsertToPairs(const Standard_Integer theIndex, const std::shared_ptr<Edge>& edge)
			{
				if (!thePairs_.insert({theIndex, edge}).second)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "duplicate data." << endl
						<< " - index: " << theIndex << endl
						<< abort(FatalError);
				}
			}

			class Edge
				: public EdgeAdaptor
				, public Global_Indexed
			{
			public:
				enum  { nbNodes = 2 };
				typedef std::array<std::shared_ptr<Node>, nbNodes> Array2;
			private:
				/*Private Data*/
				Array2 theNodes_;
			public:
				// default constructor
				Edge() = default;
				// constructors
				Edge(const Standard_Integer theIndex, const Array2& theNodes)
					: Global_Indexed(theIndex)
					, theNodes_(theNodes)
				{}
				Edge(const Standard_Integer theIndex, Array2&& theNodes)
					: Global_Indexed(theIndex)
					, theNodes_(std::move(theNodes))
				{}
				// Public functions and operators
				std::shared_ptr<Node> Next(const std::shared_ptr<Node>&) const;

				const auto& Nodes() const { return theNodes_; }
				const auto& Node0() const { return theNodes_.at(0); }
				const auto& Node1() const { return theNodes_.at(1); }

				void SetNodes(const Array2& theNodes) { theNodes_ = theNodes; }
				void SetNodes(Array2&& theNodes) { theNodes_ = std::move(theNodes); }
			};

			auto compare_edges = [](const std::shared_ptr<Edge>& edge0, const std::shared_ptr<Edge>& edge1)
			{
				return edge0->Index() < edge1->Index();
			};

			class Element
				: public Global_Indexed
			{
			public:
				enum  { nbEdges = 3 };
				typedef std::array<std::shared_ptr<Edge>, nbEdges> Array3;
			private:
				/*Private Data*/
				Array3 theEdges_;
			public:
				// default constructor
				Element() = default;
				// constructors
				Element(const Standard_Integer theIndex, const Array3& theEdges)
					: Global_Indexed(theIndex)
					, theEdges_(theEdges)
				{}
				Element(const Standard_Integer theIndex, Array3&& theEdges)
					: Global_Indexed(theIndex)
					, theEdges_(std::move(theEdges))
				{}
				// Public functions and operators
				const auto& Edges() const { return theEdges_; }
				const auto& Edge0() const { return theEdges_.at(0); }
				const auto& Edge1() const { return theEdges_.at(1); }
				const auto& Edge2() const { return theEdges_.at(2); }

				std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>, std::shared_ptr<Node>> RetrieveNodes() const;

				void SetEdges(const Array3& theEdges) { theEdges_ = theEdges; }
				void SetEdges(Array3&& theEdges) { theEdges_ = std::move(theEdges); }
			};

			std::shared_ptr<Node> Edge::Next(const std::shared_ptr<Node>& node) const
			{
				if (node == Node0())
				{
					return Node1();
				}
				return Node0();
			}

			std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>, std::shared_ptr<Node>> Element::
			RetrieveNodes() const
			{
				auto t = std::make_tuple(Edge0()->Node0(), Edge1()->Node0(), Edge2()->Node0());
				return std::move(t);
			}

			typedef std::vector<std::shared_ptr<Element>> Mesh;

			auto MakeNodes(const std::vector<Pnt3d>& thePnts)
			{
				std::vector<std::shared_ptr<Node>> nodes;
				nodes.reserve(thePnts.size());
				Standard_Integer nb_nodes = 0;
				for (const auto& x: thePnts)
				{
					auto node = std::make_shared<Node>(++nb_nodes, x);
					nodes.emplace_back(std::move(node));
				}
				return std::move(nodes);
			}
			auto MakeElements(const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<connectivity::triple>& ids)
			{
				std::vector<std::shared_ptr<Element>> elements;
				elements.reserve(ids.size());
				Standard_Integer nb_edges = 0;
				Standard_Integer nb_elements = 0;
				for (const auto& i: ids)
				{
					const auto v0 = Index_Of(i.Value(0));
					const auto v1 = Index_Of(i.Value(1));
					const auto v2 = Index_Of(i.Value(2));

					const auto& node0 = nodes.at(v0);
					const auto& node1 = nodes.at(v1);
					const auto& node2 = nodes.at(v2);

					const auto edge0 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node0, node1});
					const auto edge1 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node1, node2});
					const auto edge2 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node2, node0});
					auto element = std::make_shared<Element>(++nb_elements, Element::Array3{edge0, edge1, edge2});
					elements.emplace_back(std::move(element));
				}
				return std::move(elements);
			}
			auto RetrieveEdges(const std::vector<std::shared_ptr<Element>>& elements)
			{
				std::vector<std::shared_ptr<Edge>> edges;
				for (const auto& x: elements)
				{
					edges.emplace_back(x->Edge0());
					edges.emplace_back(x->Edge1());
					edges.emplace_back(x->Edge2());
				}
				return std::move(edges);
			}
			auto CommonEdges(const std::shared_ptr<Node>& node0, const std::shared_ptr<Node>& node1)->std::vector<std::shared_ptr<Edge>>
			{
				if (node1->NbEdges() < node0->NbEdges())
				{
					return CommonEdges(node1, node0);
				}
				std::vector<std::shared_ptr<Edge>> edges;
				for (const auto&[id, w]: node0->Edges())
				{
					auto edge = w.lock();
					Debug_Null_Pointer(edge);
					auto next = edge->Next(node0);
					if (next == node1)
					{
						edges.emplace_back(std::move(edge));
					}
				}
				return std::move(edges);
			}
			void ConnectEdges(const std::shared_ptr<Edge>& edge, const std::vector<std::shared_ptr<Edge>>& edges)
			{
				for (const auto& e: edges)
				{
					if (e != edge)
					{
						edge->InsertToPairs(e->Index(), e);
					}
				}
			}
			void ConnectEdgesAndNodes(const std::vector<std::shared_ptr<Edge>>& edges)
			{
				std::for_each(edges.begin(), edges.end(), [](const std::shared_ptr<Edge>& edge)
					{
						const auto& node0 = edge->Node0();
						const auto& node1 = edge->Node1();
						node0->InsertToEdges(edge->Index(), edge);
						node1->InsertToEdges(edge->Index(), edge);
					});
			}
			void ConnectEdgesAndNodes(const Mesh& mesh)
			{
				ConnectEdgesAndNodes(RetrieveEdges(mesh));
			}
			auto ConnectEdges(const std::shared_ptr<Edge>& edge)
			{
				auto edges = CommonEdges(edge->Node0(), edge->Node1());
				for (const auto& edge: edges)
				{
					ConnectEdges(edge, edges);
				}
				return std::move(edges);
			}
			void ConnectEdges(const std::vector<std::shared_ptr<Element>>& elements)
			{
				const auto edges = RetrieveEdges(elements);
				std::set<std::shared_ptr<Edge>, decltype(compare_edges)> comp(compare_edges);
				for (const auto& x: edges)
				{
					comp.insert(x);
				}
				while (!comp.empty())
				{
					auto current = *comp.begin();
					auto others = ConnectEdges(current);
					for (const auto& edge: others)
					{
						comp.erase(edge);
					}
					comp.erase(current);
				}
			}
			auto MakeMesh(const Entity3d_Triangulation& theTriangulation)
			{
				auto elements = MakeElements(MakeNodes(theTriangulation.Points()), theTriangulation.Connectivity());
				ConnectEdges(elements);
				return std::move(elements);
			}
			auto RetrieveNodes(const Mesh& theMesh)
			{
				std::set<std::shared_ptr<Node>, decltype(compare_nodes)> comp(compare_nodes);
				for (const auto& element: theMesh)
				{
					auto [node0, node1, node2] = element->RetrieveNodes();
					comp.insert(node0);
					comp.insert(node1);
					comp.insert(node2);
				}
				std::vector<std::shared_ptr<Node>> nodes;
				std::copy(comp.begin(), comp.end(), std::back_inserter(nodes));
				return std::move(nodes);
			}
			auto RetrieveNodes(const std::vector<std::shared_ptr<Edge>>& edges)
			{
				std::set<std::shared_ptr<Node>, decltype(compare_nodes)> comp(compare_nodes);
				for (const auto& edge: edges)
				{
					comp.insert(edge->Node0());
					comp.insert(edge->Node1());
				}
				std::vector<std::shared_ptr<Node>> nodes;
				std::copy(comp.begin(), comp.end(), std::back_inserter(nodes));
				return std::move(nodes);
			}
			void Renumber(const Mesh& theMesh, Standard_Integer& nb_edges, Standard_Integer& nb_nodes)
			{
				// renumbering the nodes
				const auto nodes = RetrieveNodes(theMesh);
				for (const auto& node: nodes)
				{
					node->SetIndex(++nb_nodes);
				}
				// renumbering the edges
				const auto edges = RetrieveEdges(theMesh);
				for (const auto& edge: edges)
				{
					edge->SetIndex(++nb_edges);
				}
			}
			auto RetrieveBoundaries(const Mesh& theMesh)
			{
				std::vector<std::shared_ptr<Edge>> boundaries;
				for (const auto& edge: RetrieveEdges(theMesh))
				{
					if (!edge->NbPairs())
					{
						boundaries.emplace_back(edge);
					}
				}
				return std::move(boundaries);
			}
			auto RetrieveBoundaryNodes(const Mesh& mesh)
			{
				auto nodes = RetrieveNodes(RetrieveBoundaries(mesh));
				return std::move(nodes);
			}
			auto RetrieveGeometries(const std::vector<std::shared_ptr<Node>>& nodes)
			{
				std::vector<Pnt3d> coords;
				coords.reserve(nodes.size());
				std::for_each(nodes.begin(), nodes.end(), [&coords](const std::shared_ptr<Node>& node)
					{
						coords.emplace_back(node->Coord());
					});
				return std::move(coords);
			}
			auto CalcAvgCoord(const std::vector<std::shared_ptr<Node>>& nodes)
			{
				Debug_If_Condition(nodes.empty());
				auto c = Pnt3d::null;
				for (const auto& x: nodes)
				{
					c += x->Coord();
				}
				return c / static_cast<Standard_Real>(nodes.size());
			}
		}
	}
}

void tnbLib::Merge3d_Triangulation::Perform()
{
	typedef geoLib::mergeTris3d::Node Node;
	enum class NodeStatus { alive, killed };
	typedef geoLib::mergeTris3d::SuperNode SuperNode;
	
	// making the meshes to retrieve the boundaries
	const auto mesh = geoLib::mergeTris3d::MakeMesh(*Triangulation());
	// connecting the entities
	geoLib::mergeTris3d::ConnectEdgesAndNodes(mesh);
	geoLib::mergeTris3d::ConnectEdges(mesh);
	// retrieve the boundary nodes
	const auto nodes = geoLib::mergeTris3d::RetrieveBoundaryNodes(mesh);
	std::cout << "nb. of boundary nodes = " << nodes.size() << std::endl;
	const auto bnd_box = Geo_BoxTools::GetBox(geoLib::mergeTris3d::RetrieveGeometries(nodes), 0);
	const auto dim = bnd_box.Diameter();
	// registering the nodes
	Geo3d_BalPrTree<std::shared_ptr<SuperNode>> engine;
	engine.BUCKET_SIZE = 4;
	engine.SetGeometryCoordFunc([](const std::shared_ptr<SuperNode>& node)-> const Pnt3d& {return node->coord; });
	engine.SetGeometryRegion(bnd_box.Expanded(bnd_box.Diameter() * 1.0e-4));
	auto search_region = [&engine](const Pnt3d& theCoord, const Standard_Real radius)
	{
		auto sr = Geo_BoxTools::GetBox(theCoord, radius);
		std::vector<std::shared_ptr<SuperNode>> items;
		engine.GeometrySearch(sr, items);
		std::vector<std::shared_ptr<SuperNode>> nodes;
		for (const auto& i: items)
		{
			if (i->coord.Distance(theCoord) <= radius)
			{
				nodes.emplace_back(i);
			}
		}
		return std::move(nodes);
	};
	//.
	//* Create a search engine to track super nodes
	//.
	const auto radius = Radius();
	Standard_Integer k = 0;
	for (const auto& node: nodes)
	{
		// search the region
		auto found = search_region(node->Coord(), radius);
		if (found.size() > 1)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " something went wrong." << endl
				<< abort(FatalError);
		}
		if (found.empty())
		{// register the node into the engine
			auto super_node = std::make_shared<SuperNode>(SuperNode{ ++k, node->Coord(), {node} });
			engine.InsertToGeometry(super_node);
		}
		else
		{
			const auto& super_node = found.at(0);
			super_node->nodes.emplace_back(node);
		}
	}
	// Calculate the avg. value to merge the points
	std::vector<std::shared_ptr<SuperNode>> super_nodes;
	engine.RetrieveFromGeometryTo(super_nodes);
	for (const auto& x: super_nodes)
	{
		x->coord = geoLib::mergeTris3d::CalcAvgCoord(x->nodes);
		for (const auto& node: x->nodes)
		{
			node->SetCoord(x->coord);
			node->SetSuper(x);
		}
	}
	Standard_Integer nb_nodes = 0;
	std::map<Standard_Integer, std::pair<NodeStatus, Standard_Integer>> merged;
	auto get_new_id = [&merged](const Standard_Integer i)
	{
		if (merged.at(i).first IS_EQUAL NodeStatus::killed)
		{// The node is already killed.
			return merged.at(merged.at(i).second).second;
		}// The node is alive!
		return merged.at(i).second;
	};
	for (const auto& node: geoLib::mergeTris3d::RetrieveNodes(mesh))
	{
		if (const auto father = node->Super().lock())
		{// the boundary node
			//++nb_nodes;
			if (father->MinId() == node->Index())
			{
				merged.insert({ node->Index(), {NodeStatus::alive, ++nb_nodes} });
			}
			else
			{
				merged.insert({ node->Index(), {NodeStatus::killed, father->MinId()} });
			}
		}
		else
		{
			merged.insert({ node->Index(), {NodeStatus::alive, ++nb_nodes} });
		}
	}
	// retrieving the compressed points (alive nodes)
	std::vector<Pnt3d> coords;
	for (const auto& node: geoLib::mergeTris3d::RetrieveNodes(mesh))
	{
		if (merged.at(node->Index()).first == NodeStatus::alive)
		{
			coords.emplace_back(node->Coord());
		}
	}
	std::vector<connectivity::triple> ids;
	ids.reserve(theTriangulation_->NbConnectivity());
	for (const auto& i: theTriangulation_->Connectivity())
	{
		auto v0 = i.Value(0);
		auto v1 = i.Value(1);
		auto v2 = i.Value(2);
		connectivity::triple t;
		t.Value(0) = get_new_id(v0);
		if (NOT t.Value(0))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - Invalid index has been detected." << endl
				<< abort(FatalError);
		}
		t.Value(1) = get_new_id(v1);
		if (NOT t.Value(1))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - Invalid index has been detected." << endl
				<< abort(FatalError);
		}
		t.Value(2) = get_new_id(v2);
		if (NOT t.Value(2))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - Invalid index has been detected." << endl
				<< abort(FatalError);
		}
		ids.emplace_back(std::move(t));
	}
	theMerged_ = std::make_shared<Entity3d_Triangulation>(std::move(coords), std::move(ids));
	Change_IsDone() = Standard_True;
}

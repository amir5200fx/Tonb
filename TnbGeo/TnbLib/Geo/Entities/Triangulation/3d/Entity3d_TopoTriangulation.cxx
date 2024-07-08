#include <Entity3d_TopoTriangulation.hxx>
#include <Global_Indexed.hxx>

namespace tnbLib
{
	namespace topoTriangulation
	{
		// Forward Declarations
		class Edge;
		class Element;

		class NodeAdaptor
		{
			/*Private Data*/
			std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;
		protected:
			// default constructor
			NodeAdaptor() = default;
		public:
			// Public functions and operators
			auto NbEdges() const { return static_cast<Standard_Integer>(theEdges_.size()); }
			const auto& Edges() const { return theEdges_; }

			void InsertToEdges(const Standard_Integer theIndex, const std::shared_ptr<Edge>&);
		};

		void NodeAdaptor::InsertToEdges(const Standard_Integer theIndex, const std::shared_ptr<Edge>& theEdge)
		{
			if (NOT theEdges_.insert({theIndex, theEdge}).second)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " duplicate data!" << endl
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
			// constructors
			Node(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}
			// Public functions and operators
			const auto& Coord() const { return theCoord_; }
		};

		static auto comp_nodes = [](const std::shared_ptr<Node>& node0, const std::shared_ptr<Node>& node1)
		{
			return node0->Index() < node1->Index();
		};

		class EdgeAdaptor
		{
			/*Private Data*/
			std::weak_ptr<Element> theLeft_;
			std::weak_ptr<Element> theRight_;
		protected:
			// defautl constructor
			EdgeAdaptor() = default;
		public:
			// Public functions and operators
			const auto& Left() const { return theLeft_; }
			const auto& Right() const { return theRight_; }

			void SetLeft(const std::shared_ptr<Element>& theElement) { theLeft_ = theElement; }
			void SetRight(const std::shared_ptr<Element>& theElement) { theRight_ = theElement; }
		};

		class Edge
			: public EdgeAdaptor
			, public Global_Indexed
		{
		public:
			typedef std::array<std::shared_ptr<Node>, 2> Array2;
		private:
			/*Private Data*/
			Array2 theNodes_;
		public:
			// constructors
			Edge(const Standard_Integer theIndex, const Array2& theNodes)
				: Global_Indexed(theIndex)
				, theNodes_(theNodes)
			{}
			// Public functions and operators
			const auto& Nodes() const { return theNodes_; }

			const auto& Node0() const { return theNodes_.at(0); }
			const auto& Node1() const { return theNodes_.at(1); }

			std::shared_ptr<Node> Other(const std::shared_ptr<Node>&) const;
		};

		static auto comp_edges = [](const std::shared_ptr<Edge>& edge0, const std::shared_ptr<Edge>& edge1)
		{
			return edge0->Index() < edge1->Index();
		};

		std::shared_ptr<Node> Edge::Other(const std::shared_ptr<Node>& theNode) const
		{
			if (theNode IS_EQUAL Node0())
			{
				return Node1();
			}
			else if (theNode IS_EQUAL Node1())
			{
				return Node0();
			}
			FatalErrorIn(FunctionSIG) << endl
				<< " the node doesn't belong to the edge." << endl
				<< abort(FatalError);
			return nullptr;
		}

		class Element
			: public Global_Indexed
		{
		public:
			typedef std::array<std::shared_ptr<Edge>, 3> Array3;
		private:
			/*Private Data*/
			Array3 theEdges_;
		public:
			// constructors
			Element(const Standard_Integer theIndex, const Array3& theEdges)
				: Global_Indexed(theIndex)
				, theEdges_(theEdges)
			{}
			// Public functions and operators
			const auto& Edges() const { return theEdges_; }

			const auto& Edge0() const { return theEdges_.at(0); }
			const auto& Edge1() const { return theEdges_.at(1); }
			const auto& Edge2() const { return theEdges_.at(2); }

			std::vector<std::shared_ptr<Node>> RetrieveNodes() const;
		};

		std::vector<std::shared_ptr<Node>> Element::RetrieveNodes() const
		{
			std::set<std::shared_ptr<Node>, decltype(comp_nodes)> comp(comp_nodes);
			comp.insert(Edge0()->Node0());
			comp.insert(Edge0()->Node1());
			comp.insert(Edge1()->Node0());
			comp.insert(Edge1()->Node1());
			comp.insert(Edge2()->Node0());
			comp.insert(Edge2()->Node1());
			std::vector<std::shared_ptr<Node>> nodes;
			std::copy(comp.begin(), comp.end(), std::back_inserter(nodes));
			return std::move(nodes);
		}

		auto find_common_edge(const std::shared_ptr<Node>& node0, const std::shared_ptr<Node>& node1) -> std::shared_ptr<Edge>
		{
			if (node1->NbEdges() < node0->NbEdges())
			{
				return find_common_edge(node1, node0);
			}
			for (const auto& [id, w_edge] : node0->Edges())
			{
				auto edge = w_edge.lock();
				Debug_Null_Pointer(edge);
				if (edge->Other(node0) IS_EQUAL node1)
				{
					return std::move(edge);
				}
			}
			return nullptr;
		}

		auto make_nodes(const std::vector<Pnt3d>& points)
		{
			std::vector<std::shared_ptr<Node>> nodes;
			Standard_Integer nb_nodes = 0;
			for (const auto& pt: points)
			{
				auto node = std::make_shared<Node>(++nb_nodes, pt);
				nodes.emplace_back(std::move(node));
			}
			return std::move(nodes);
		}

		auto make_edge(const std::shared_ptr<Node>& node0, const std::shared_ptr<Node>& node1,
		               Standard_Integer& nb_edges) -> std::pair<std::shared_ptr<Edge>, Standard_Boolean>
		{
			if (auto edge = find_common_edge(node0, node1))
			{
				return { std::move(edge), Standard_False };
			}
			auto edge = std::make_shared<Edge>(++nb_edges, Edge::Array2{node0, node1});
			node0->InsertToEdges(edge->Index(), edge);
			node1->InsertToEdges(edge->Index(), edge);
			return { std::move(edge), Standard_True };
		}

		auto make_elements(const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<connectivity::triple>& ids)
		{
			Standard_Integer nb_edges = 0;
			Standard_Integer nb_elements = 0;
			std::vector<std::shared_ptr<Element>> elements;
			std::cout << "nodes' size: " << nodes.size() << std::endl;
			int k = 0;
			for (const auto& i: ids)
			{
				std::cout << "i = " << k++ << std::endl;
				const auto v0 = Index_Of(i.Value(0));
				const auto v1 = Index_Of(i.Value(1));
				const auto v2 = Index_Of(i.Value(2));
				std::cout << "v0 = " << v0 << ", v1 = " << v1 << ", v2 = " << v2 << "\n";
				const auto& node0 = nodes.at(v0);
				const auto& node1 = nodes.at(v1);
				const auto& node2 = nodes.at(v2);

				const auto edge0 = make_edge(node0, node1, nb_edges);
				const auto edge1 = make_edge(node1, node2, nb_edges);
				const auto edge2 = make_edge(node2, node0, nb_edges);

				auto element = std::make_shared<Element>(++nb_elements, Element::Array3{edge0.first, edge1.first, edge2.first});

				edge0.second ? edge0.first->SetLeft(element) : edge0.first->SetRight(element);
				edge1.second ? edge1.first->SetLeft(element) : edge1.first->SetRight(element);
				edge2.second ? edge2.first->SetLeft(element) : edge2.first->SetRight(element);

				elements.emplace_back(std::move(element));
			}
			std::cout << "finished\n";
			return std::move(elements);
		}

		auto retrieve_edges(const std::vector<std::shared_ptr<Element>>& elements)
		{
			std::set<std::shared_ptr<Edge>, decltype(comp_edges)> comp(comp_edges);
			std::for_each(elements.begin(), elements.end(), [&comp](const std::shared_ptr<Element>& element)
				{
					comp.insert(element->Edge0());
					comp.insert(element->Edge1());
					comp.insert(element->Edge2());
				});
			std::vector<std::shared_ptr<Edge>> edges;
			std::copy(comp.begin(), comp.end(), std::back_inserter(edges));
			return std::move(edges);
		}

		auto make_segment(const std::shared_ptr<Edge>& edge)
		{
			connectivity::dual d;
			d.Value(0) = edge->Node0()->Index();
			d.Value(1) = edge->Node1()->Index();
			return std::move(d);
		}

		auto make_segments(const std::vector<std::shared_ptr<Edge>>& edges)
		{
			std::vector<connectivity::dual> segments;
			segments.reserve(edges.size());
			std::for_each(edges.begin(), edges.end(), [&segments](const std::shared_ptr<Edge>& edge)
				{
					segments.emplace_back(make_segment(edge));
				});
			return std::move(segments);
		}

		auto make_TAS(const std::vector<std::shared_ptr<Edge>>& edges)
		{
			std::vector<connectivity::dual> tas;
			tas.reserve(edges.size());
			std::for_each(edges.begin(), edges.end(), [&tas](const std::shared_ptr<Edge>& edge)
				{
					connectivity::dual d;
					const auto left = edge->Left().lock();
					if (NOT left)
					{
						FatalErrorIn(FunctionSIG) << endl
							<< " the edge doesn't have and element on its left side!" << endl
							<< abort(FatalError);
					}
					d.Value(0) = left->Index();
					const auto right = edge->Left().lock();
					right ? d.Value(1) = right->Index() : d.Value(1) = 0;
					tas.emplace_back(std::move(d));
				});
			return std::move(tas);
		}
	}
}

void tnbLib::Entity3d_TopoTriangulation::Construct(const Entity3d_Triangulation& theTriangulations)
{
	std::cout << "nodes\n";
	const auto nodes = tnbLib::topoTriangulation::make_nodes(theTriangulations.Points());
	std::cout << "elements\n";
	const auto elements = topoTriangulation::make_elements(nodes, theTriangulations.Connectivity());
	std::cout << "edges\n";
	const auto edges = topoTriangulation::retrieve_edges(elements);
	std::cout << "segments\n";
	theSegments_ = topoTriangulation::make_segments(edges);
	std::cout << "tas..\n";
	theTAS_ = topoTriangulation::make_TAS(edges);
}

tnbLib::Entity3d_TopoTriangulation::Entity3d_TopoTriangulation(const Entity3d_Triangulation& theTriangulation)
{
	Import(theTriangulation);
}

tnbLib::Entity3d_TopoTriangulation::Entity3d_TopoTriangulation(const std::vector<Pnt3d>& thePnts,
	const std::vector<connectivity::triple>& theTris)
{
	Import(Entity3d_Triangulation(thePnts, theTris));
}

void tnbLib::Entity3d_TopoTriangulation::Import(const Entity3d_Triangulation& theTriangulation)
{
	Points() = theTriangulation.Points();
	Connectivity() = theTriangulation.Connectivity();
	Construct(theTriangulation);
}

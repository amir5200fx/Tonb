#include <Entity3d_TriShell.hxx>

#include <Entity3d_SurfTriangulation.hxx>
#include <Global_Indexed.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	namespace triShellLib
	{
		// Forward Declarations
		class Edge;
		class NodeAdaptor
		{
			/*Private Data*/
			std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;
		protected:
			// default constructor
			NodeAdaptor() = default;
			// constructors
		public:
			// Public functions and operators
			Standard_Integer NbEdges() const { return static_cast<Standard_Integer>(theEdges_.size()); }

			const auto& Edges() const { return theEdges_; }

			void InsertEdge(const Standard_Integer theIndex, const std::shared_ptr<Edge>& theEdge);
		};

		class Node
			: public Global_Indexed
			, public NodeAdaptor
		{
			/*Private Data*/
			Pnt3d theCoord_;
		public:
			// default constructor

			// constructors
			Node(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: theCoord_(theCoord)
				, Global_Indexed(theIndex)
			{}
			// Public functions and operators
			const auto& Coord() const { return theCoord_; }
		};

		class Edge
			: public Global_Indexed
		{
		public:
			typedef std::array<std::shared_ptr<Node>, 2> Array2;
		private:
			/*Private Data*/
			Array2 theNodes_;
			std::weak_ptr<Edge> thePair_;
		public:
			// default constructor

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
			const auto& Nodes() const { return theNodes_; }
			const auto& Node0() const { return theNodes_.at(0); }
			const auto& Node1() const { return theNodes_.at(1); }
			const auto& Pair() const { return thePair_; }

			Standard_Boolean IsPaired() const { return !thePair_.lock(); }
			std::shared_ptr<Node> Next(const std::shared_ptr<Node>&) const;

			void SetPair(const std::weak_ptr<Edge>& thePair) { thePair_ = thePair; }
		};

		auto compare_edges = [](const std::shared_ptr<Edge>& edge0, const std::shared_ptr<Edge>& edge1)
		{
			return edge0->Index() < edge1->Index();
		};

		std::shared_ptr<Node> Edge::Next(const std::shared_ptr<Node>& node) const
		{
			if (Node0() == node)
			{
				return Node1();
			}
			return Node0();
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
			// default constructor

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
		};

		auto RetrieveNodes(const std::vector<Pnt3d>& thePnts)
		{
			std::vector<std::shared_ptr<Node>> nodes;
			nodes.reserve(thePnts.size());
			Standard_Integer k = 0;
			for (const auto& pt: thePnts)
			{
				auto node = std::make_shared<Node>(++k, pt);
				nodes.emplace_back(std::move(node));
			}
			return std::move(nodes);
		}

		auto RetrieveElements(const std::vector<connectivity::triple>& theElements,
		                      const std::vector<std::shared_ptr<Node>>& theNodes)
		{
			std::vector<std::shared_ptr<Element>> elements;
			Standard_Integer nb_elements = 0;
			Standard_Integer nb_edges = 0;
			for (const auto& elm: theElements)
			{
				const auto v0 = Index_Of(elm.Value(0));
				const auto v1 = Index_Of(elm.Value(1));
				const auto v2 = Index_Of(elm.Value(2));
				const auto& node0 = theNodes.at(v0);
				const auto& node1 = theNodes.at(v1);
				const auto& node2 = theNodes.at(v2);
				const auto edge0 = std::make_shared<Edge>(++nb_edges, Edge::Array2{{ node0, node1 }});
				{
					node0->InsertEdge(edge0->Index(), edge0);
					node1->InsertEdge(edge0->Index(), edge0);
				}
				const auto edge1 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node1, node2});
				{
					node1->InsertEdge(edge1->Index(), edge1);
					node2->InsertEdge(edge1->Index(), edge1);
				}
				const auto edge2 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node2, node0});
				{
					node2->InsertEdge(edge2->Index(), edge2);
					node0->InsertEdge(edge2->Index(), edge2);
				}
				auto element = std::make_shared<Element>(++nb_elements, Element::Array3{edge0, edge1, edge2});
				elements.emplace_back(std::move(element));
			}
			return std::move(elements);
		}

		auto CommonEdges(const std::shared_ptr<Node>& node0,
		                 const std::shared_ptr<Node>& node1) -> std::vector<std::shared_ptr<Edge>>
		{
			if (node0->NbEdges() < node1->NbEdges())
			{
				return CommonEdges(node1, node0);
			}
			std::vector<std::shared_ptr<Edge>> edges;
			for (const auto&[id, w]: node0->Edges())
			{
				auto edge = w.lock();
				auto next = edge->Next(node0);
				if (next IS_EQUAL node1)
				{
					edges.emplace_back(edge);
				}
			}
			return std::move(edges);
		}

		auto FindPair(const std::shared_ptr<Edge>& edge)
		{
			const auto& node0 = edge->Node0();
			const auto& node1 = edge->Node1();
			auto edges = CommonEdges(node0, node1);
			if (edges.size() == 2)
			{
				if (edges.at(0) IS_EQUAL edge)
				{
					return edges.at(1);
				}
				return edges.at(0);
			}
			return std::shared_ptr<Edge>();
		}

		void ConnectEdges(const std::vector<std::shared_ptr<Element>>& theElements)
		{
			std::set<std::shared_ptr<Edge>, decltype(compare_edges)> comp(compare_edges);
			for (const auto& elm: theElements)
			{
				comp.insert(elm->Edge0());
				comp.insert(elm->Edge1());
				comp.insert(elm->Edge2());
			}
			while(!comp.empty())
			{
				auto current = *comp.begin();
				if (auto pair = FindPair(current))
				{
					current->SetPair(pair);
					pair->SetPair(current);
					comp.erase(pair);
				}
			}
		}

		auto RetrieveElements(const Entity3d_Triangulation& theSurfMesh)
		{
			const auto nodes = RetrieveNodes(theSurfMesh.Points());
			auto elements = RetrieveElements(theSurfMesh.Connectivity(), nodes);
			return std::move(elements);
		}

		auto RetrieveEdges(const std::vector<std::shared_ptr<Element>>& elements)
		{
			std::vector<std::shared_ptr<Edge>> edges;
			for (const auto& elm: elements)
			{
				edges.emplace_back(elm->Edge0());
				edges.emplace_back(elm->Edge1());
				edges.emplace_back(elm->Edge2());
			}
			return std::move(edges);
		}
	}
}

void tnbLib::triShellLib::NodeAdaptor::InsertEdge(const Standard_Integer theIndex, const std::shared_ptr<Edge>& theEdge)
{
	if (!theEdges_.insert({theIndex, theEdge}).second)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " duplicate data has been detected." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

tnbLib::Entity3d_TriShell::Entity3d_TriShell(const Entity3d_Triangulation& theMesh)
{
	Import(theMesh);
}

void tnbLib::Entity3d_TriShell::Import(const Entity3d_Triangulation& theSurfMesh)
{
	const auto elements = triShellLib::RetrieveElements(theSurfMesh);
	triShellLib::ConnectEdges(elements);
	const auto edges = triShellLib::RetrieveEdges(elements);
	for (const auto& edge: edges)
	{
		if (NOT edge->IsPaired())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the surface mesh is not closed." << endl
				<< abort(FatalError);
		}
	}
	theCoords_ = theSurfMesh.Points();
	theElements_ = theSurfMesh.Connectivity();
}

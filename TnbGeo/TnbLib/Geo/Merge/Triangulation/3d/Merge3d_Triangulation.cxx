#include <Merge3d_Triangulation.hxx>

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

			class NodeAdaptor
			{
				/*Private Data*/
				std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;
			protected:
				// default constructor
				NodeAdaptor() = default;
			public:
				// Public functions and operators
				Standard_Integer NbEdges() const { return static_cast<Standard_Integer>(theEdges_.size()); }
				const auto& Edges() const { return theEdges_; }

				void InsertToEdges(const Standard_Integer theIndex, const std::weak_ptr<Edge>&);
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

				void SetEdges(const Array3& theEdges) { theEdges_ = theEdges; }
				void SetEdges(Array3&& theEdges) { theEdges_ = std::move(theEdges); }
			};

			typedef std::vector<std::shared_ptr<Element>> Mesh;

			auto MakeNodes(const std::vector<Pnt3d>& thePnts, Standard_Integer& nb_nodes)
			{
				std::vector<std::shared_ptr<Node>> nodes;
				nodes.reserve(thePnts.size());
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
					node0->InsertToEdges(edge0->Index(), edge0);
					node1->InsertToEdges(edge0->Index(), edge0);
					const auto edge1 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node1, node2});
					node1->InsertToEdges(edge1->Index(), edge1);
					node2->InsertToEdges(edge1->Index(), edge1);
					const auto edge2 = std::make_shared<Edge>(++nb_edges, Edge::Array2{node2, node0});
					node2->InsertToEdges(edge2->Index(), edge2);
					node0->InsertToEdges(edge2->Index(), edge2);
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
			auto ConnectEdges(const std::shared_ptr<Edge>& edge, const std::vector<std::shared_ptr<Edge>>& edges)
			{
				for (const auto& e: edges)
				{
					if (e != edge)
					{
						edge->InsertToPairs(e->Index(), e);
					}
				}
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
				}
			}
			auto MakeMesh(const Entity3d_Triangulation& theTriangulation)
			{
				Standard_Integer nb_nodes = 0;
				auto elements = MakeElements(MakeNodes(theTriangulation.Points(), nb_nodes), theTriangulation.Connectivity());
				ConnectEdges(elements);
				return std::move(elements);
			}
		}
	}
}

void tnbLib::Merge3d_Triangulation::Perform()
{
	struct Node
	{
		Pnt3d coord;
		Standard_Integer id;
	};
	// making the meshes to retrieve the boundaries
	std::vector<geoLib::mergeTris3d::Mesh> meshes;
	for (const auto& tris: theTriangulations_)
	{
		auto mesh = geoLib::mergeTris3d::MakeMesh(*tris);
		meshes.emplace_back(std::move(mesh));
	}
	// register all of the nodes into an array
	std::vector<std::shared_ptr<Node>> nodes;
	Standard_Integer nb_nodes = 0;
	for (const auto& tris: theTriangulations_)
	{
		for (const auto& pt: tris->Points())
		{
			auto node = std::make_shared<Node>(Node{ pt, ++nb_nodes });
			nodes.push_back(std::move(node));
		}
	}

}

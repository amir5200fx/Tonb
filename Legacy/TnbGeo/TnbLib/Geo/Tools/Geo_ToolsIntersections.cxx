#include <Geo_Tools.hxx>

#include <Global_Indexed.hxx>
#include <Entity2d_Triangle.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_AdTree.hxx>
#include <Geo2d_DelTri_CGAL.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>

namespace tnbLib
{

	namespace intrsctLib
	{

		//- Forward Declarations
		class Triangle;

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

			std::map<Standard_Integer, std::weak_ptr<Triangle>> theTriangles_;

		public:

			//- default constructor

			Node()
			{}

			//- constructors

			Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}


			//- public functions and operators

			const auto& Coord() const
			{
				return theCoord_;
			}

			const auto& Triabgles() const
			{
				return theTriangles_;
			}

			void ImportToTriangles(const std::shared_ptr<Triangle>& theTriangle);

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

		};

		class Triangle
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;
			std::shared_ptr<Node> theNode2_;

		public:

			Triangle()
			{}

			Triangle
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Node>& theNode0, 
				const std::shared_ptr<Node>& theNode1,
				const std::shared_ptr<Node>& theNode2
			)
				: Global_Indexed(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
				, theNode2_(theNode2)
			{}

			Triangle
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1,
				std::shared_ptr<Node>&& theNode2
			)
				: Global_Indexed(theIndex)
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
				, theNode2_(std::move(theNode2))
			{}

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			const auto& Node2() const
			{
				return theNode2_;
			}

			const auto& GetNode(const Standard_Integer theIndex) const
			{
				return (&theNode0_)[theIndex];
			}

			void SetNode0(const std::shared_ptr<Node>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode1(const std::shared_ptr<Node>& theNode)
			{
				theNode1_ = theNode;
			}

			void  SetNode2(const std::shared_ptr<Node>& theNode)
			{
				theNode2_ = theNode;
			}
		};

		//- Forward Declarations
		class SuperTriangle;

		class SuperNode
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;

			std::map<Standard_Integer, std::shared_ptr<Node>> theNodes_;
			std::map<Standard_Integer, std::weak_ptr<SuperTriangle>> theTriangles_;

		public:

			typedef Pnt2d ptType;

			//- default constructor
			SuperNode()
			{}


			//- constructors

			SuperNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}


			//- public functions and operators

			const auto& Nodes() const
			{
				return theNodes_;
			}

			const auto& Triangles() const
			{
				return theTriangles_;
			}

			const auto& Coord() const
			{
				return theCoord_;
			}

			void ImportToNodes(const std::shared_ptr<Node>& theNode);

			void ImportToTriangles(const std::shared_ptr<SuperTriangle>& theTriangle);

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			static const auto& GetCoord(const std::shared_ptr<SuperNode>& n)
			{
				return n->Coord();
			}

		};

		class SuperTriangle
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<Triangle> theTriangle_;

			std::shared_ptr<SuperNode> theNode0_;
			std::shared_ptr<SuperNode> theNode1_;
			std::shared_ptr<SuperNode> theNode2_;

		public:


			//- default constructor

			SuperTriangle()
			{}


			//- constructors

			SuperTriangle
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SuperNode>& theNode0, 
				const std::shared_ptr<SuperNode>& theNode1, 
				const std::shared_ptr<SuperNode>& theNode2, 
				const std::shared_ptr<Triangle>& theTriangle
			)
				: Global_Indexed(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
				, theNode2_(theNode2)
				, theTriangle_(theTriangle)
			{}


			//- public functions and operators

			const auto& GetTriangle() const
			{
				return theTriangle_;
			}

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			const auto& Node2() const
			{
				return theNode2_;
			}

			void SetTriangle(const std::shared_ptr<Triangle>& theTri)
			{
				theTriangle_ = theTri;
			}

			void SetNode0(const std::shared_ptr<SuperNode>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode1(const std::shared_ptr<SuperNode>& theNode)
			{
				theNode1_ = theNode;
			}

			void  SetNode2(const std::shared_ptr<SuperNode>& theNode)
			{
				theNode2_ = theNode;
			}
		};

		struct Info
		{
			Standard_Integer nbNodes;
			Standard_Integer nbTris;

			Standard_Integer nbSuperNodes;
			Standard_Integer nbSuperTris;

			Info()
				: nbNodes(0)
				, nbTris(0)
				, nbSuperNodes(0)
				, nbSuperTris(0)
			{}
		};

		
		static Standard_Real srchRadius = 1.0E-6;
	}

	std::pair
		<
		std::vector<std::shared_ptr<intrsctLib::Triangle>>,
		std::vector<std::shared_ptr<intrsctLib::Node>>
		> 
		RetrieveTriangles
		(
			const std::vector<Entity2d_Triangle>& theTriangles
		)
	{
		Standard_Integer nbTriangles = 0;
		Standard_Integer nbNodes = 0;

		std::vector<std::shared_ptr<intrsctLib::Node>> nodes;
		std::vector<std::shared_ptr<intrsctLib::Triangle>> triangles;
		nodes.reserve(3 * theTriangles.size());
		triangles.reserve(theTriangles.size());
		for (const auto& x : theTriangles)
		{
			const auto& p0 = x.P0();
			const auto& p1 = x.P1();
			const auto& p2 = x.P2();

			auto node0 = std::make_shared<intrsctLib::Node>(++nbNodes, p0);
			auto node1 = std::make_shared<intrsctLib::Node>(++nbNodes, p1);
			auto node2 = std::make_shared<intrsctLib::Node>(++nbNodes, p2);

			nodes.push_back(node0);
			nodes.push_back(node1);
			nodes.push_back(node2);

			auto tri = std::make_shared<intrsctLib::Triangle>(++nbTriangles, node0, node1, node2);

			node0->ImportToTriangles(tri);
			node1->ImportToTriangles(tri);
			node2->ImportToTriangles(tri);

			triangles.push_back(std::move(tri));
		}

		auto t = std::make_pair(std::move(triangles), std::move(nodes));
		return std::move(t);
	}

	typedef Geo_AdTree<std::shared_ptr<intrsctLib::SuperNode>> AdTree;

	auto RetrieveBoundingBox(const Entity2d_Triangle& tri)
	{
		std::vector<Pnt2d> pnts;
		pnts.reserve(3);

		pnts.push_back(tri.P0());
		pnts.push_back(tri.P1());
		pnts.push_back(tri.P2());

		auto b = Geo_BoxTools::GetBox(pnts, 1.0E-6);
		return std::move(b);
	}

	auto RetrieveBoundingBox(const std::vector<Entity2d_Triangle>& tris)
	{
		auto iter = tris.begin();
		auto b = RetrieveBoundingBox(*iter);

		iter++;
		while (iter NOT_EQUAL tris.end())
		{
			b = Geo_BoxTools::Union(b, RetrieveBoundingBox(*iter));
			iter++;
		}
		return std::move(b);
	}

	auto RetrieveIntersection(const Entity2d_Triangle& t0, const Entity2d_Triangle& t1)
	{
		auto pnts = Geo_Tools::Intersecction_cgal(t0, t1);
		if (pnts.size() >= 3)
		{
			cgalLib::Geo2d_DelTri dt(pnts);
			dt.Perform();
			Debug_If_Condition_Message(NOT dt.IsDone(), "the algorithm is not performed!");

			return dt.Triangulation();
		}
		else
		{
			return std::shared_ptr<Entity2d_Triangulation>();
		}
	}

	auto RetrieveIntersections
	(
		const Entity2d_Triangle& tri,
		const std::map<Standard_Integer, std::shared_ptr<intrsctLib::SuperTriangle>>& tris
	)
	{
		std::vector<Entity2d_Triangle> elements;
		for (const auto& t : tris)
		{
			const auto& x = t.second->GetTriangle();

			Entity2d_Triangle target(x->Node0()->Coord(), x->Node1()->Coord(), x->Node2()->Coord());
			if (const auto result = RetrieveIntersection(tri, target))
			{
				const auto& pnts = result->Points();
				for (const auto& id : result->Connectivity())
				{
					const auto& p0 = pnts[Index_Of(id.Value(0))];
					const auto& p1 = pnts[Index_Of(id.Value(1))];
					const auto& p2 = pnts[Index_Of(id.Value(2))];

					Entity2d_Triangle ent(p0, p1, p2);
					elements.push_back(std::move(ent));
				}
			}
		}
		return std::move(elements);
	}

	auto RetrieveTriangles(const std::vector<std::shared_ptr<intrsctLib::SuperNode>>& nodes)
	{
		std::map<Standard_Integer, std::shared_ptr<intrsctLib::SuperTriangle>> triangles;
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			const auto& superTris = x->Triangles();
			for (const auto& t : superTris)
			{
				auto st = t.second.lock();
				Debug_Null_Pointer(st);

				auto paired = std::make_pair(st->Index(), std::move(st));
				auto insert = triangles.insert(std::move(paired));
				if (NOT insert.second)
				{
					//- duplicate data: do nothing
				}
			}
		}
		return std::move(triangles);
	}

	auto RetrieveIntersections(const Entity2d_Triangle& tri, AdTree& tree)
	{
		const auto b = RetrieveBoundingBox(tri);

		std::vector<std::shared_ptr<intrsctLib::SuperNode>> nodes;
		tree.GeometrySearch(b, nodes);

		auto tris = RetrieveTriangles(nodes);

		auto elements = RetrieveIntersections(tri, tris);
		return std::move(elements);
	}

	auto ImportNode(const Pnt2d& coord, intrsctLib::Info& info, AdTree& tree)
	{
		std::vector<std::shared_ptr<intrsctLib::SuperNode>> nodes;
		tree.GeometrySearch(intrsctLib::srchRadius, coord, nodes);

		auto node = std::make_shared<intrsctLib::Node>(++info.nbNodes, coord);
		Debug_Null_Pointer(node);

		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			if (x->Coord().Distance(coord) <= intrsctLib::srchRadius)
			{		
				x->ImportToNodes(node);

				auto t = std::make_pair(x, std::move(node));
				return std::move(t);
			}
		}

		auto superNode = std::make_shared<intrsctLib::SuperNode>(++info.nbSuperNodes, coord);
		Debug_Null_Pointer(superNode);

		superNode->ImportToNodes(node);

		tree.InsertToGeometry(superNode);

		auto t = std::make_pair(std::move(superNode), std::move(node));
		return std::move(t);
	}

	void ImportTriangle(const Entity2d_Triangle& tri, intrsctLib::Info& info, AdTree& tree)
	{
		const auto& p0 = tri.P0();
		const auto& p1 = tri.P1();
		const auto& p2 = tri.P2();

		auto[v0, n0] = ImportNode(p0, info, tree);
		auto[v1, n1] = ImportNode(p1, info, tree);
		auto[v2, n2] = ImportNode(p2, info, tree);

		auto t = std::make_shared<intrsctLib::Triangle>(++info.nbTris, n0, n1, n2);
		Debug_Null_Pointer(t);

		n0->ImportToTriangles(t);
		n1->ImportToTriangles(t);
		n2->ImportToTriangles(t);

		auto superTri = std::make_shared<intrsctLib::SuperTriangle>(++info.nbSuperTris, v0, v1, v2, t);
		Debug_Null_Pointer(superTri);

		v0->ImportToTriangles(superTri);
		v1->ImportToTriangles(superTri);
		v2->ImportToTriangles(superTri);
	}

	auto RetrieveIntersections(const Entity2d_Triangle& tri, intrsctLib::Info& info, AdTree& tree)
	{
		auto items = RetrieveIntersections(tri, tree);

		ImportTriangle(tri, info, tree);

		return std::move(items);
	}

	auto RetrieveIntersections(const std::vector<Entity2d_Triangle>& tris, intrsctLib::Info& info, AdTree& tree)
	{
		std::vector<Entity2d_Triangle> list;
		for (const auto& x : tris)
		{
			auto items = RetrieveIntersections(x, info, tree);
			for (auto& t : items)
			{
				list.push_back(std::move(t));
			}
		}
		return std::move(list);
	}
}

void tnbLib::intrsctLib::Node::ImportToTriangles(const std::shared_ptr<Triangle>& theTriangle)
{
	auto paired = std::make_pair(theTriangle->Index(), theTriangle);
	auto insert = theTriangles_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theTriangle->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::intrsctLib::SuperNode::ImportToNodes(const std::shared_ptr<Node>& theNode)
{
	auto paired = std::make_pair(theNode->Index(), theNode);
	auto insert = theNodes_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theNode->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::intrsctLib::SuperNode::ImportToTriangles(const std::shared_ptr<SuperTriangle>& theTriangle)
{
	auto paired = std::make_pair(theTriangle->Index(), theTriangle);
	auto insert = theTriangles_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theTriangle->Index() << endl
			<< abort(FatalError);
	}
}

std::vector<tnbLib::Entity2d_Triangle>
tnbLib::Geo_Tools::Intersections
(
	const std::vector<Entity2d_Triangle>& theTriangles
)
{
	auto domain = RetrieveBoundingBox(theTriangles);
	const auto d = domain.Diameter();

	intrsctLib::srchRadius = d * 1.0E-5;

	AdTree tree;
	tree.SetGeometryRegion(domain.Expanded(d*1.0E-6));
	tree.SetGeometryCoordFunc(&intrsctLib::SuperNode::GetCoord);

	intrsctLib::Info info;

	auto items = RetrieveIntersections(theTriangles, info, tree);
	tree.Clear();
	return std::move(items);
}
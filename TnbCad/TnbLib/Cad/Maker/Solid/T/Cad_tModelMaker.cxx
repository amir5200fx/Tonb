#include <Cad_tModelMaker.hxx>

#include <Cad_tEdgeMaker.hxx>
#include <Cad_tSurfaceMaker.hxx>
#include <Cad_tSurfaceMakerInfo.hxx>
#include <Cad_tModelMakerInfo.hxx>
#include <Cad_tModelMaker_PairCrvCriterion.hxx>
#include <Cad_tEdgeMakerInfo_Absolute.hxx>
#include <Cad_tSurfaceMakerInfo_Absolute.hxx>
#include <Cad_tModelMakerInfo_Absolute.hxx>
#include <Cad_tModelMaker_OnePtDistPairCrvCriterion.hxx>
#include <Cad_BlockEntity.hxx>
#include <Cad_TModel.hxx>
#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Edges.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Curve.hxx>
#include <TModel_Surface.hxx>
#include <Geo_PrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>

unsigned short tnbLib::Cad_tModelMaker::verbose = 0;

const std::shared_ptr<tnbLib::Cad_tModelMaker::MakerInfo> tnbLib::Cad_tModelMaker::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_tModelMaker::MakerInfo>();

const std::shared_ptr<tnbLib::Cad_tModelMaker_PairCrvCriterion> tnbLib::Cad_tModelMaker::DEFAULT_CRITERION =
std::make_shared<cadLib::tModelMaker_OnePtDistPairCrvCriterion>();

namespace tnbLib
{

	class Cad_tModelMakerRunTimeSetConfigs
	{

		/*Private Data*/

	public:

		// default constructor [1/21/2022 Amir]

		Cad_tModelMakerRunTimeSetConfigs()
		{
			SetConfigs();
		}

		// public functions and operators [1/21/2022 Amir]

		static void SetConfigs();
	};
}

void tnbLib::Cad_tModelMakerRunTimeSetConfigs::SetConfigs()
{
	auto& myInfo = *Cad_tModelMaker::DEFAULT_INFO;

	myInfo.edgeInfo = std::make_shared<tnbLib::Cad_tEdgeMakerInfo_Absolute>(Precision::Confusion());
	myInfo.surfInfo = std::make_shared<tnbLib::Cad_tSurfaceMakerInfo_Absolute>();
	myInfo.modelInfo = std::make_shared<tnbLib::Cad_tModelMakerInfo_Absolute>();
}

static const tnbLib::Cad_tModelMakerRunTimeSetConfigs mytModelMakerRunTimeSetConfigsObj;

void tnbLib::Cad_tModelMaker::MakerInfo::Check() const
{
	if (NOT edgeInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "Edge info is null" << endl
			<< abort(FatalError);
	}

	if (NOT surfInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "Surface info is null" << endl
			<< abort(FatalError);
	}

	if (NOT modelInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "Model info is null" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad_tModelMaker::SetCornerManager
(
	std::shared_ptr<TModel_CornerManager>&& theManager,
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	theSolid->CornersRef() = std::move(theManager);
}

void tnbLib::Cad_tModelMaker::SetSegmentManager
(
	std::shared_ptr<TModel_SegmentManager>&& theManager,
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	theSolid->SegmentsRef() = std::move(theManager);
}

void tnbLib::Cad_tModelMaker::SetFaceManager
(
	std::shared_ptr<TModel_FaceManager>&& theManager,
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	theSolid->FacesRef() = std::move(theManager);
}

namespace tnbLib
{

	class MergeSegments
		: public Global_Done
	{

		/*Private Data*/

	public:

		// Forward Declarations [1/6/2022 Amir]
		class Edge;

		class NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;

		protected:

			// default constructor [1/6/2022 Amir]

			NodeAdaptor()
			{}

			// constructors [1/6/2022 Amir]

		public:


			// public functions and operators [1/6/2022 Amir]

			Standard_Boolean IsOrphan() const;

			auto NbEdges() const
			{
				return (Standard_Integer)theEdges_.size();
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			void ImportToEdges(const std::shared_ptr<Edge>&);
		};

		class Node
			: public Global_Indexed
			, public NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<TModel_Vertex>> theVertices_;

			Standard_Real thePrec_;

			Pnt3d theCoord_;

		public:

			typedef Pnt3d ptType;

			//- default constructor

			Node()
				: thePrec_(0)
			{}

			//- constructors

			Node(const Standard_Integer theIndex, const Pnt3d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
				, thePrec_(0)
			{}

			Node
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<TModel_Vertex>& theVtx
			)
				: Global_Indexed(theIndex)
				, thePrec_(0)
			{
				ImportToVertices(theVtx);
				SetCoord(theVtx->Coord());
			}

			Node(const std::shared_ptr<TModel_Vertex>& theVtx)
				: thePrec_(0)
			{
				ImportToVertices(theVtx);
				SetCoord(theVtx->Coord());
			}


			// public functions and operators [8/22/2021 Amir]

			const auto& Vertices() const
			{
				return theVertices_;
			}

			auto Precision() const
			{
				return thePrec_;
			}

			const auto& Coord() const
			{
				return theCoord_;
			}

			void ImportToVertices(const std::shared_ptr<TModel_Vertex>&);

			void SetPrecision(const Standard_Real x)
			{
				thePrec_ = x;
			}

			void SetCoord(const Pnt3d& theCoord)
			{
				theCoord_ = theCoord;
			}

		};

		class EdgeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<TModel_Edge>> theEdges_;

		protected:

			//- default constructor

			EdgeAdaptor()
			{}

			//- constructors

		public:

			//- public functions and operators

			Standard_Boolean IsFree() const;
			Standard_Boolean IsManifold() const;

			const auto& Edges() const
			{
				return theEdges_;
			}

			void ImportToEdges(const std::shared_ptr<TModel_Edge>&);
		};

		class Edge
			: public Global_Indexed
			, public EdgeAdaptor
		{

			/*Private Data*/

		protected:

			//- default constructor

			Edge()
			{}

			//- constructors

			explicit Edge(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

			
		public:

			//- public functions and operators

			virtual Standard_Boolean IsSegment() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual std::vector<std::shared_ptr<Node>> RetrieveNodes() const = 0;
			virtual void RetrieveNodesTo(std::vector<std::shared_ptr<Node>>&) const = 0;

		};

		class SegmentEdge
			: public Edge
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			// default constructor [1/7/2022 Amir]

			SegmentEdge()
			{}

			// constructors [1/7/2022 Amir]

			explicit SegmentEdge(const Standard_Integer theIndex)
				: Edge(theIndex)
			{}

			SegmentEdge
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Node>& theNode0,
				const std::shared_ptr<Node>& theNode1
			)
				: Edge(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			SegmentEdge
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1
			)
				: Edge(theIndex)
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}


			// public functions and operators [1/7/2022 Amir]

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			void SetNode0(const std::shared_ptr<Node>& theNode)
			{
				theNode0_ = theNode;
			}

			void SetNode0(std::shared_ptr<Node>&& theNode)
			{
				theNode0_ = std::move(theNode);
			}

			void SetNode1(const std::shared_ptr<Node>& theNode)
			{
				theNode1_ = theNode;
			}

			void SetNode1(std::shared_ptr<Node>&& theNode)
			{
				theNode1_ = std::move(theNode);
			}

			// override functions and operators [1/7/2022 Amir]

			Standard_Boolean IsSegment() const override
			{
				return Standard_True;
			}

			std::vector<std::shared_ptr<Node>> RetrieveNodes() const override;
			void RetrieveNodesTo(std::vector<std::shared_ptr<Node>>&) const override;

		};

		class RingEdge
			: public Edge
		{

			/*Private Data*/

			std::shared_ptr<Node> theNode_;

		public:

			// default constructor [1/7/2022 Amir]

			RingEdge()
			{}


			// constructors [1/7/2022 Amir]

			explicit RingEdge(const Standard_Integer theIndex)
				: Edge(theIndex)
			{}

			RingEdge
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Node>& theNode
			)
				: Edge(theIndex)
				, theNode_(theNode)
			{}

			RingEdge
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode
			)
				: Edge(theIndex)
				, theNode_(std::move(theNode))
			{}


			// public functions and operators [1/7/2022 Amir]

			const auto& GetNode() const
			{
				return theNode_;
			}

			void SetNode(const std::shared_ptr<Node>& theNode)
			{
				theNode_ = theNode;
			}

			// override functions and operators [1/7/2022 Amir]

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			std::vector<std::shared_ptr<Node>> RetrieveNodes() const override;
			void RetrieveNodesTo(std::vector<std::shared_ptr<Node>>&) const override;
		};

	private:

		/*Private Data*/

		const std::vector<std::shared_ptr<TModel_Edge>>& theEdges_;

		std::shared_ptr<Cad_tModelMakerInfo> theInfo_;
		std::shared_ptr<Cad_tModelMaker_PairCrvCriterion> thePairCriterion_;


		std::map<Standard_Integer, std::shared_ptr<Node>> theIdToNodeMap_;
		std::vector<std::shared_ptr<Edge>> theMergedEdges_;

	public:

		//- default constructor


		//- constructors

		MergeSegments
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges,
			const std::shared_ptr<Cad_tModelMakerInfo>& theInfo,
			const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>& thePairCriterion
		)
			: theEdges_(theEdges)
			, theInfo_(theInfo)
			, thePairCriterion_(thePairCriterion)
		{}


		//- public functions and operators

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& MakerInfo() const
		{
			return theInfo_;
		}

		const auto& MergedEdges() const
		{
			return theMergedEdges_;
		}

		const auto& PairCriterion() const
		{
			return thePairCriterion_;
		}

		const auto& IdToNodeMap() const
		{
			return theIdToNodeMap_;
		}

		void CalcIdToNodeMap();
		void CalcMergedEdges();

		void Perform();

		std::shared_ptr<Node> FindNode(const std::shared_ptr<TModel_Vertex>&) const;


		//- static functions and operators

		static std::pair<std::shared_ptr<Edge>, Standard_Boolean> 
			MakeNewEdge
			(
				const std::shared_ptr<Node>&,
				const std::shared_ptr<Node>&, 
				const std::shared_ptr<TModel_Edge>&, 
				const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>&
			);
		static std::pair<std::shared_ptr<Edge>, Standard_Boolean> 
			MakeNewRing
			(
				const std::shared_ptr<Node>&,
				const std::shared_ptr<TModel_Edge>&,
				const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>&
			);
		static std::shared_ptr<Edge> 
			CommonEdge
			(
				const std::shared_ptr<Node>&,
				const std::shared_ptr<Node>&
			);

		static std::vector<std::shared_ptr<Node>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Edge>>&
			);
		static std::vector<Pnt3d> 
			RetrieveCoords
			(
				const std::vector<std::shared_ptr<Node>>&
			);
		static Entity3d_Box 
			CalcBoundingBox
			(
				const std::vector<std::shared_ptr<Node>>&
			);

		//static std::vector<std::shared_ptr<Edge>> RetrieveEdges(const std::vector<std::shared_ptr<TModel_Edge>>&);
	};
}

std::vector<std::shared_ptr<tnbLib::MergeSegments::Node>>
tnbLib::MergeSegments::SegmentEdge::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(2);

	nodes.push_back(Node0());
	nodes.push_back(Node1());
	return std::move(nodes);
}

void tnbLib::MergeSegments::SegmentEdge::RetrieveNodesTo
(
	std::vector<std::shared_ptr<Node>>& theNodes
) const
{
	theNodes.push_back(Node0());
	theNodes.push_back(Node1());
}

std::vector<std::shared_ptr<tnbLib::MergeSegments::Node>>
tnbLib::MergeSegments::RingEdge::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(1);

	nodes.push_back(GetNode());
	return std::move(nodes);
}

void tnbLib::MergeSegments::RingEdge::RetrieveNodesTo
(
	std::vector<std::shared_ptr<Node>>& nodes
) const
{
	nodes.push_back(GetNode());
}

Standard_Boolean
tnbLib::MergeSegments::NodeAdaptor::IsOrphan() const
{
	return (Standard_Boolean)theEdges_.empty();
}

void tnbLib::MergeSegments::NodeAdaptor::ImportToEdges
(
	const std::shared_ptr<Edge>& theEdge
)
{
	if (NOT theEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "null ptr has been detected!" << endl
			<< abort(FatalError);
	}

	auto paired = std::make_pair(theEdge->Index(), theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate item has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::MergeSegments::Node::ImportToVertices
(
	const std::shared_ptr<TModel_Vertex>& theVtx
)
{
	if (NOT theVtx)
	{
		FatalErrorIn(FunctionSIG)
			<< "null ptr has been detected!" << endl
			<< abort(FatalError);
	}

	auto paired = std::make_pair(theVtx->Index(), theVtx);
	auto insert = theVertices_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate item has been detected!" << endl
			<< " - index: " << theVtx->Index() << endl
			<< abort(FatalError);
	}
}

std::vector<std::shared_ptr<tnbLib::MergeSegments::Node>>
tnbLib::MergeSegments::RetrieveNodes
(
	const std::vector<std::shared_ptr<Edge>>& edges
)
{
	std::map<Standard_Integer, std::shared_ptr<Node>> regNodes;
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		auto nodes = x->RetrieveNodes();
		for (auto& n : nodes)
		{
			Debug_Null_Pointer(n);
			auto paired = std::make_pair(n->Index(), std::move(n));
			auto insert = regNodes.insert(std::move(paired));
			if (NOT insert.second)
			{
				// do nothing! duplicate data [1/31/2022 Amir]
			}
		}
	}

	std::vector<std::shared_ptr<Node>> vertices;
	vertices.reserve(regNodes.size());

	for (auto& x : regNodes)
	{
		auto& n = x.second;
		Debug_Null_Pointer(n);

		vertices.push_back(std::move(n));
	}
	return std::move(vertices);
}

std::vector<tnbLib::Pnt3d>
tnbLib::MergeSegments::RetrieveCoords
(
	const std::vector<std::shared_ptr<Node>>& vertices
)
{
	std::vector<Pnt3d> pts;
	pts.reserve(vertices.size());

	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		pts.push_back(x->Coord());
	}
	return std::move(pts);
}

tnbLib::Entity3d_Box
tnbLib::MergeSegments::CalcBoundingBox
(
	const std::vector<std::shared_ptr<Node>>& nodes
)
{
	const auto pts = RetrieveCoords(nodes);
	auto b = Geo_BoxTools::GetBox(pts, 0);
	return std::move(b);
}

Standard_Boolean
tnbLib::MergeSegments::EdgeAdaptor::IsFree() const
{
	return (Standard_Boolean)(theEdges_.size() IS_EQUAL 1);
}

Standard_Boolean
tnbLib::MergeSegments::EdgeAdaptor::IsManifold() const
{
	return (Standard_Boolean)(theEdges_.size() IS_EQUAL 2);
}

void tnbLib::MergeSegments::EdgeAdaptor::ImportToEdges(const std::shared_ptr<TModel_Edge>& theEdge)
{
	if (NOT theEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "null edge has been detected!" << endl
			<< abort(FatalError);
	}

	auto paired = std::make_pair(theEdge->Index(), theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate item has been detected!" << endl
			<< "index: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}

namespace tnbLib
{

	auto RetrieveNodes(const std::vector<std::shared_ptr<TModel_Edge>>& edges)
	{
		std::vector<std::shared_ptr<TModel_Vertex>> vertices;
		vertices.reserve(2 * edges.size());
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);
			x->RetrieveVerticesTo(vertices);
		}
		return std::move(vertices);
	}

	auto RetrieveCoords(const std::vector<std::shared_ptr<TModel_Vertex>>& vertices)
	{
		std::vector<Pnt3d> pts;
		pts.reserve(vertices.size());
		for (const auto& x : vertices)
		{
			Debug_Null_Pointer(x);
			pts.push_back(x->Coord());
		}
		return std::move(pts);
	}

	auto CalcBoundingBox(const std::vector<std::shared_ptr<TModel_Vertex>>& vertices)
	{
		const auto pts = RetrieveCoords(vertices);
		auto b = Geo_BoxTools::GetBox(pts, 0);
		return std::move(b);
	}
}

void tnbLib::MergeSegments::CalcIdToNodeMap()
{
	if (NOT MakerInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	const auto& edges = Edges();
	const auto unMergedNodes = ::tnbLib::RetrieveNodes(edges);

	auto b = ::tnbLib::CalcBoundingBox(unMergedNodes);
	const auto d = b.Diameter();

	b.OffSet(1.0E-3*d);

	Geo_PrTree<std::shared_ptr<Node>> engine;
	engine.SetGeometryCoordFunc
	([](const std::shared_ptr<Node>& v)-> const Pnt3d& {Debug_Null_Pointer(v); return v->Coord(); });
	engine.SetGeometryRegion(b);

	const auto radius = MakerInfo()->Radius();
	const auto dp = Pnt3d(radius, radius, radius);

	const auto tol = MakerInfo()->Tolerance();

	Standard_Integer nbNodes = 0;
	for (const auto& x : unMergedNodes)
	{
		Debug_Null_Pointer(x);

		std::vector<std::shared_ptr<Node>> candidates;

		const auto& o = x->Coord();
		auto region = Entity3d_Box(o - dp, o + dp);

		engine.GeometrySearch(region, candidates);

		if (candidates.empty())
		{
			auto newNode = std::make_shared<MergeSegments::Node>(++nbNodes, x->Coord());
			engine.InsertToGeometry(newNode);

			newNode->SetPrecision(0);
			newNode->ImportToVertices(x);
		}
		else
		{
			auto minDist = RealLast();
			std::shared_ptr<Node> found;

			for (const auto& node : candidates)
			{
				Debug_Null_Pointer(node);
				auto dis = Distance(node->Coord(), x->Coord());

				if (dis < minDist)
				{
					minDist = dis;
					found = node;
				}
			}

			if (minDist <= tol)
			{
				found->ImportToVertices(x);
				found->SetPrecision(std::max(found->Precision(), minDist));
			}
			else
			{
				auto newNode = std::make_shared<MergeSegments::Node>(++nbNodes, x->Coord());
				engine.InsertToGeometry(newNode);

				newNode->SetPrecision(0);
			}
		}
	}

	std::vector<std::shared_ptr<MergeSegments::Node>> nodes;
	engine.RetrieveFromGeometryTo(nodes);

	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);

		const auto& vertices = x->Vertices();
		for (const auto& v : vertices)
		{
			Debug_Null_Pointer(v.second);

			auto paired = std::make_pair(v.second->Index(), x);
			auto insert = theIdToNodeMap_.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate item is found!" << endl
					<< abort(FatalError);
			}
		}
	}
}

void tnbLib::MergeSegments::CalcMergedEdges()
{
	Standard_Integer nbEdges = 0;
	for (const auto& x : Edges())
	{
		if (NOT x->IsDegenerated())
		{
			auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(x);
			Debug_Null_Pointer(g);

			if (g->IsRing())
			{
				auto ring = std::dynamic_pointer_cast<TModel_RingEdge>(g);
				Debug_Null_Pointer(ring);

				auto n = FindNode(ring->Vtx());

				Debug_Null_Pointer(n);
				auto ringPaired = MergeSegments::MakeNewRing(n, x, PairCriterion());

				if (ringPaired.second)
				{
					auto& newEdge = ringPaired.first;
					newEdge->SetIndex(++nbEdges);

					newEdge->ImportToEdges(x);

					n->ImportToEdges(newEdge);

					theMergedEdges_.push_back(std::move(newEdge));
				}
				else
				{
					auto& edge = ringPaired.first;
					edge->ImportToEdges(x);
				}
			}
			else if (g->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<TModel_SegmentEdge>(g);
				Debug_Null_Pointer(seg);

				auto n0 = FindNode(seg->Vtx0());
				auto n1 = FindNode(seg->Vtx1());

				Debug_Null_Pointer(n0);
				Debug_Null_Pointer(n1);
				auto edgePaired = MergeSegments::MakeNewEdge(n0, n1, x, PairCriterion());
				if (edgePaired.second)
				{
					auto& newEdge = edgePaired.first;
					newEdge->SetIndex(++nbEdges);

					newEdge->ImportToEdges(x);

					n0->ImportToEdges(newEdge);
					n1->ImportToEdges(newEdge);		

					theMergedEdges_.push_back(std::move(newEdge));
				}
				else
				{
					auto& edge = edgePaired.first;
					edge->ImportToEdges(x);

					//theMergedEdges_.push_back(std::move(edge));
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unspecified type of segment is detected!" << endl
					<< abort(FatalError);
			}
		}
	}
}

void tnbLib::MergeSegments::Perform()
{
	if (MakerInfo()->Radius() < MakerInfo()->Tolerance())
	{
		FatalErrorIn(FunctionSIG)
			<< " the radius must be bigger than tolerance" << endl
			<< " - radius: " << MakerInfo()->Radius() << endl
			<< " - tol: " << MakerInfo()->Tolerance() << endl
			<< abort(FatalError);
	}

	CalcIdToNodeMap();
	CalcMergedEdges();
	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::MergeSegments::Node>
tnbLib::MergeSegments::FindNode
(
	const std::shared_ptr<TModel_Vertex>& theVtx
) const
{
	Debug_Null_Pointer(theVtx);
	auto iter = theIdToNodeMap_.find(theVtx->Index());
	if (iter IS_EQUAL theIdToNodeMap_.end())
	{
		return nullptr;
	}
	auto item = iter->second;
	return std::move(item);
}

std::pair<std::shared_ptr<tnbLib::MergeSegments::Edge>, Standard_Boolean>
tnbLib::MergeSegments::MakeNewEdge
(
	const std::shared_ptr<Node>& theNode0,
	const std::shared_ptr<Node>& theNode1,
	const std::shared_ptr<TModel_Edge>& theEdge, 
	const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>& theCriterion
)
{
	if (NOT theNode0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the node0 is null" << endl
			<< abort(FatalError);
	}

	if (NOT theNode1)
	{
		FatalErrorIn(FunctionSIG)
			<< " the node1 is null" << endl
			<< abort(FatalError);
	}

	if (theNode0->IsOrphan())
	{
		auto edge = std::make_shared<SegmentEdge>(0, theNode0, theNode1);
		auto t = std::make_pair(std::move(edge), Standard_True);
		return std::move(t);
	}

	if (theNode1->IsOrphan())
	{
		auto edge = std::make_shared<SegmentEdge>(0, theNode0, theNode1);
		auto t = std::make_pair(std::move(edge), Standard_True);
		return std::move(t);
	}

	auto Seg = std::dynamic_pointer_cast<TModel_SegmentEdge>(theEdge);
	Debug_Null_Pointer(Seg);

	if (auto edge = CommonEdge(theNode0, theNode1))
	{
		for (const auto& x : edge->Edges())
		{
			const auto& e = x.second;
			Debug_Null_Pointer(e);
			if (auto seg = std::dynamic_pointer_cast<TModel_SegmentEdge>(e))
			{
				if (theCriterion->ArePaired(seg->Curve(), Seg->Curve()))
				{
					auto t = std::make_pair(std::move(edge), Standard_False);
					return std::move(t);
				}
			}
		}
	}

	auto edge = std::make_shared<SegmentEdge>(0, theNode0, theNode1);
	auto t = std::make_pair(std::move(edge), Standard_True);
	return std::move(t);
}

std::pair<std::shared_ptr<tnbLib::MergeSegments::Edge>, Standard_Boolean>
tnbLib::MergeSegments::MakeNewRing
(
	const std::shared_ptr<Node>& theNode, 
	const std::shared_ptr<TModel_Edge>& theEdge, 
	const std::shared_ptr<Cad_tModelMaker_PairCrvCriterion>& theCriterion
)
{
	if (NOT theNode)
	{
		FatalErrorIn(FunctionSIG)
			<< "the node is null" << endl
			<< abort(FatalError);
	}

	if (theNode->IsOrphan())
	{
		auto edge = std::make_shared<RingEdge>(0, theNode);
		auto t = std::make_pair(std::move(edge), Standard_True);
		return std::move(t);
	}

	auto ring = std::dynamic_pointer_cast<TModel_RingEdge>(theEdge);
	Debug_Null_Pointer(ring);

	const auto& edges = theNode->Edges();
	for (const auto& x : edges)
	{
		auto e = x.second.lock();
		Debug_Null_Pointer(e);

		if (e->IsRing())
		{
			auto iring = std::dynamic_pointer_cast<MergeSegments::RingEdge>(e);
			Debug_Null_Pointer(iring);

			for (const auto& ie : iring->Edges())
			{
				Debug_Null_Pointer(ie.second);
				auto ir = std::dynamic_pointer_cast<TModel_RingEdge>(ie.second);
				Debug_Null_Pointer(ir);
				if (theCriterion->ArePaired(ir->Curve(), ring->Curve()))
				{
					auto t = std::make_pair(std::move(e), Standard_False);
					return std::move(t);
				}
			}
		}
	}

	auto edge = std::make_shared<RingEdge>(0, theNode);
	auto t = std::make_pair(std::move(edge), Standard_True);
	return std::move(t);
}

std::shared_ptr<tnbLib::MergeSegments::Edge>
tnbLib::MergeSegments::CommonEdge
(
	const std::shared_ptr<Node>& theNode0,
	const std::shared_ptr<Node>& theNode1
)
{
	if (theNode0->NbEdges() <= theNode1->NbEdges())
	{
		const auto& edges = theNode0->Edges();
		for (const auto& x : edges)
		{
			auto ed = x.second.lock();
			Debug_Null_Pointer(ed);

			if (auto seg = std::dynamic_pointer_cast<SegmentEdge>(ed))
			{
				if (seg->Node0() IS_EQUAL theNode1)
				{
					return std::move(ed);
				}

				if (seg->Node1() IS_EQUAL theNode1)
				{
					return std::move(ed);
				}
			}
		}
	}
	else
	{
		auto edge = CommonEdge(theNode1, theNode0);
		return std::move(edge);
	}
	return nullptr;
}

namespace tnbLib
{

	void ReplaceVertex
	(
		const std::shared_ptr<MergeSegments::Node>& node,
		const std::shared_ptr<TModel_Vertex>& vertex
	)
	{
		for (const auto& x : node->Vertices())
		{
			const auto& n = x.second;
			Debug_Null_Pointer(n);

			auto edges = n->RetrieveEdges();
			Debug_If_Condition_Message(edges.empty(), "the edge and the sub-vertices are not linked!");

			for (const auto& e : edges)
			{
				Debug_Null_Pointer(e);
				if (auto seg = std::dynamic_pointer_cast<TModel_SegmentEdge>(e))
				{
					if (seg->Vtx0() IS_EQUAL n)
					{
						seg->SetVtx0(vertex);
					}
					else if (seg->Vtx1() IS_EQUAL n)
					{
						seg->SetVtx1(vertex);
					}
					else
					{
						FatalErrorIn(FunctionSIG)
							<< " contradictory data has been detected." << endl
							<< abort(FatalError);
					}		
				}
				else if (auto ring = std::dynamic_pointer_cast<TModel_RingEdge>(e))
				{
					ring->SetVtx(vertex);
				}

				vertex->ImportToEdges(e->Index(), e);
				for (const auto& s : n->RetrieveSurfaces())
				{
					Debug_Null_Pointer(s);
					vertex->ImportToSurfaces(s->Index(), s);
				}
			}
		}
	}

	auto CreateVertices(const std::vector<std::shared_ptr<MergeSegments::Node>>& nodes)
	{
		Standard_Integer nbNodes = 0;

		std::vector<std::shared_ptr<TModel_Vertex>> vertices;
		vertices.reserve(nodes.size());
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			const auto& coord = x->Coord();

			auto vertex = std::make_shared<TModel_Vertex>(++nbNodes, coord);
			Debug_Null_Pointer(vertex);

			ReplaceVertex(x, vertex);

			vertices.push_back(std::move(vertex));
		}
		return std::move(vertices);
	}

	auto RetriveEdges
	(
		const std::map<Standard_Integer, std::shared_ptr<TModel_Edge>>& theMap
	)
	{
		std::vector<std::shared_ptr<TModel_Edge>> edges;
		edges.reserve(theMap.size());
		for (const auto& x : theMap)
		{
			edges.push_back(x.second);
		}
		return std::move(edges);
	}

	auto CreateSegments(const std::vector<std::shared_ptr<MergeSegments::Edge>>& edges)
	{
		Standard_Integer nbSegments = 0;

		std::vector<std::shared_ptr<TModel_Paired>> segments;
		segments.reserve(edges.size());
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);
			if (x->IsManifold())
			{
				auto subs = RetriveEdges(x->Edges());
				Debug_If_Condition(subs.size() NOT_EQUAL 2);

				++nbSegments;

				auto tri = subs.at(0)->Triangulation();
				if (NOT tri)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge is not discretized." << endl
						<< abort(FatalError);
				}
				auto seg = std::make_shared<TModel_ManifoldPaired>
					(
						nbSegments,
						"segment" + std::to_string(nbSegments), 
						std::move(subs.at(0)), std::move(subs.at(1))
						);
				Debug_Null_Pointer(seg);
				seg->SetMesh(std::move(tri));
				segments.push_back(std::move(seg));
			}
			else
			{
				auto subs = RetriveEdges(x->Edges());
				if (subs.empty())
				{
					FatalErrorIn(FunctionSIG)
						<< "no edge has been found." << endl
						<< abort(FatalError);
				}
				auto tri = subs.at(0)->Triangulation();
				if (NOT tri)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge is not discretized." << endl
						<< abort(FatalError);
				}
				++nbSegments;

				auto seg = std::make_shared<TModel_nonManifoldPaired>
					(
						nbSegments, 
						"segment" + std::to_string(nbSegments)
						);
				Debug_Null_Pointer(seg);
				seg->SetMesh(std::move(tri));
				seg->EdgesRef() = x->Edges();
				segments.push_back(std::move(seg));
			}
		}
		return std::move(segments);
	}

	auto MakeCornerManager(const std::vector<std::shared_ptr<TModel_Vertex>>& vertices)
	{
		auto block = std::make_shared<Cad_BlockEntity<TModel_Vertex>>("Default Block Point", vertices);
		auto manager = std::make_shared<TModel_CornerManager>("Default Block Point", block);
		return std::move(manager);
	}

	auto MakeSegmentManager(const std::vector<std::shared_ptr<TModel_Paired>>& segments)
	{
		auto block = std::make_shared<Cad_BlockEntity<TModel_Paired>>("Default Block Edge", segments);
		auto manager = std::make_shared<TModel_SegmentManager>("Default Block Edge", block);
		return std::move(manager);
	}

	auto MakeFaceManager(const std::vector<std::shared_ptr<TModel_Surface>>& surfaces)
	{
		auto block = std::make_shared<Cad_BlockEntity<TModel_Surface>>("Default Block Surface", surfaces);
		auto manager = std::make_shared<TModel_FaceManager>("Default Block Surface", block);
		return std::move(manager);
	}

	void LinkEdges(const std::shared_ptr<TModel_SegmentManager>& manager)
	{
		Debug_Null_Pointer(manager);

		auto segments = manager->RetrieveEntities();
		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x);
			x->SetPairs();
		}
	}
}

#include <Cad_Tools.hxx>
#include <Cad_TModel.hxx>
#include <Cad_tSurfaceMaker.hxx>
#include <TModel_Surface.hxx>

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

namespace tnbLib
{

	auto RetrieveSurfaces
	(
		const TopoDS_Shape& theShape,
		const std::shared_ptr<Cad_tSurfaceMaker::MakerInfo>& theInfo
	)
	{
		Standard_Integer k = 0;
		std::vector<std::shared_ptr<TModel_Surface>> surfaceList;
		for (
			TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
			aFaceExp.More();
			aFaceExp.Next()
			)
		{
			auto raw = TopoDS::Face(aFaceExp.Current());

			if (NOT raw.IsNull())
			{
				auto surfMaker = std::make_shared<Cad_tSurfaceMaker>(raw, theInfo);
				Debug_Null_Pointer(surfMaker);

				surfMaker->Perform();
				Debug_If_Condition_Message(NOT surfMaker->IsDone(), "the algorithm is not performed!");

				auto s = surfMaker->Surface();
				Debug_Null_Pointer(s);

				s->SetIndex(++k);
				s->SetName("surface " + std::to_string(k));

				surfaceList.push_back(std::move(s));
			}
		}
		return std::move(surfaceList);
	}

	void LinkEdges(const std::vector<std::shared_ptr<TModel_Edge>>& theEdges)
	{
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			if (NOT x->IsDegenerated())
			{
				if (auto seg = std::dynamic_pointer_cast<TModel_SegmentEdge>(x))
				{
					const auto& v0 = seg->Vtx0();
					const auto& v1 = seg->Vtx1();

					Debug_Null_Pointer(v0);
					Debug_Null_Pointer(v1);

					v0->ImportToEdges(x->Index(), x);
					v1->ImportToEdges(x->Index(), x);
				}
				else if (auto ring = std::dynamic_pointer_cast<TModel_RingEdge>(x))
				{
					const auto& v = ring->Vtx();
					Debug_Null_Pointer(v);

					v->ImportToEdges(x->Index(), x);
				}
				else
				{
					FatalErrorIn(FunctionSIG)
						<< "unspecified type of segment has been detected!" << endl
						<< abort(FatalError);
				}
			}
		}
	}

	void RenumberingEdges(const std::vector<std::shared_ptr<TModel_Edge>>& theEdges)
	{
		Standard_Integer k = 0;
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			x->SetIndex(++k);
		}
	}

	void RenumberingNodes(const std::vector<std::shared_ptr<TModel_Edge>>& theEdges)
	{
		Standard_Integer k = 0;
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			if (NOT x->IsDegenerated())
			{
				std::vector<std::shared_ptr<TModel_Vertex>> vertices;
				x->RetrieveVerticesTo(vertices);

				for (const auto& v : vertices)
				{
					Debug_Null_Pointer(v);
					if (NOT v->Index()) v->SetIndex(++k);
				}
			}
		}
	}
}

void tnbLib::Cad_tModelMaker::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Creating TModel ********" << endl;
		Info << endl;
	}

	if (Shape().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "the shape is null" << endl
			<< abort(FatalError);
	}

	GetInfo()->Check();

	auto surfInfo = 
		std::make_shared<Cad_tSurfaceMaker::MakerInfo>
		(
			Cad_tSurfaceMaker::MakerInfo{ GetInfo()->edgeInfo, GetInfo()->surfInfo }
	);
	Debug_Null_Pointer(surfInfo);

	if (verbose)
	{
		Info << endl
			<< " Retrieving the surfaces..." << endl;
	}

	const auto surfaces = RetrieveSurfaces(Shape(), surfInfo);

	auto solid = std::make_shared<Cad_TModel>();
	Debug_Null_Pointer(solid);

	if (verbose)
	{
		Info << endl
			<< " Retrieving the edges..." << endl;
	}
	const auto edges = Cad_Tools::RetrieveEdges(surfaces);

	RenumberingEdges(edges);
	RenumberingNodes(edges);

	LinkEdges(edges);

	if (verbose)
	{
		Info << endl
			<< " Merging the segments..." << endl;
	}
	auto mergeAlg = std::make_shared<MergeSegments>(edges, GetInfo()->modelInfo, PairCriterion());
	Debug_Null_Pointer(mergeAlg);

	mergeAlg->Perform();
	Debug_If_Condition_Message(NOT mergeAlg->IsDone(), "the algorithm is not performed");

	if (verbose)
	{
		Info << endl
			<< " Retrieving the vertices..." << endl;
	}
	const auto& mergedEdges = mergeAlg->MergedEdges();

	const auto mergedNodes = MergeSegments::RetrieveNodes(mergedEdges);

	if (verbose)
	{
		Info << endl
			<< " Creating the corner manager..." << endl;
	}
	auto vertices = CreateVertices(mergedNodes);
	auto cornerManager = MakeCornerManager(vertices);

	SetCornerManager(std::move(cornerManager), solid);

	if (verbose)
	{
		Info << endl
			<< " Creating the segment manager..." << endl;
	}
	auto segments = CreateSegments(mergedEdges);
	auto segmentManagr = MakeSegmentManager(segments);

	SetSegmentManager(std::move(segmentManagr), solid);

	if (verbose)
	{
		Info << endl
			<< " Creating the face manager..." << endl;
	}
	auto faceManager = MakeFaceManager(surfaces);

	SetFaceManager(std::move(faceManager), solid);

	if (verbose)
	{
		Info << endl
			<< " Linking the segments..." << endl;
	}
	LinkEdges(solid->Segments());

	solid->SetShape(Shape());

	theModel_ = std::move(solid);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of the Creating a TModel ********" << endl;
		Info << endl;
	}
}
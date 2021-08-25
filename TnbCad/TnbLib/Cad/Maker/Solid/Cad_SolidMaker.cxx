#include <Cad_SolidMaker.hxx>

#include <TModel_Vertex.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Tools.hxx>
#include <Geo_PrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>

void tnbLib::Cad_SolidMaker::SetCornerManager
(
	std::shared_ptr<TModel_CornerManager>&& theManager,
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	theSolid->CornersRef() = std::move(theManager);
}

void tnbLib::Cad_SolidMaker::SetSegmentManager
(
	std::shared_ptr<TModel_SegmentManager>&& theManager,
	const std::shared_ptr<Cad_TModel>& theSolid
)
{
	theSolid->SegmentsRef() = std::move(theManager);
}

void tnbLib::Cad_SolidMaker::SetFaceManager
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

	public:

		//- Forward Declarations
		class Edge;

		class NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;

		protected:

			//- default constructor

			NodeAdaptor()
			{}

			//- constructors

		public:


			// public functions and operators [8/22/2021 Amir]

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

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			//- default constructor

			Edge()
			{}

			//- constructors

			Edge(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

			Edge
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Node>& theNode0, 
				const std::shared_ptr<Node>& theNode1
			)
				: Global_Indexed(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			Edge
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1
			)
				: Global_Indexed(theIndex)
				, theNode0_(std::move(theNode0))
				, theNode1_(std::move(theNode1))
			{}


			//- public functions and operators

			

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

		};

	private:

		/*Private Data*/

		const std::vector<std::shared_ptr<TModel_Edge>>& theEdges_;

		Standard_Real theTol_;
		Standard_Real theRadius_;


		std::map<Standard_Integer, std::shared_ptr<Node>> theIdToNodeMap_;
		std::vector<std::shared_ptr<Edge>> theMergedEdges_;

	public:

		//- default constructor


		//- constructors

		MergeSegments
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges,
			const Standard_Real theTol,
			const Standard_Real theRadius
		)
			: theEdges_(theEdges)
			, theTol_(theTol)
			, theRadius_(theRadius)
		{}


		//- public functions and operators

		const auto& Edges() const
		{
			return theEdges_;
		}

		auto Tolerance() const
		{
			return theTol_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		const auto& MergedEdges() const
		{
			return theMergedEdges_;
		}

		void CalcIdToNodeMap();
		void CalcMergedEdges();

		void Perform();

		std::shared_ptr<Node> FindNode(const std::shared_ptr<TModel_Vertex>&) const;


		//- static functions and operators

		static std::pair<std::shared_ptr<Edge>, Standard_Boolean> MakeNewEdge(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&);
		static std::shared_ptr<Edge> CommonEdge(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&);

		static std::vector<std::shared_ptr<Node>> RetrieveNodes(const std::vector<std::shared_ptr<Edge>>&);
		static std::vector<Pnt3d> RetrieveCoords(const std::vector<std::shared_ptr<Node>>&);
		static Entity3d_Box CalcBoundingBox(const std::vector<std::shared_ptr<Node>>&);

		static std::vector<std::shared_ptr<Edge>> RetrieveEdges(const std::vector<std::shared_ptr<TModel_Edge>>&);
	};
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
			<< abort(FatalError);
	}
}

std::vector<std::shared_ptr<tnbLib::MergeSegments::Node>> 
tnbLib::MergeSegments::RetrieveNodes
(
	const std::vector<std::shared_ptr<Edge>>& edges
)
{
	std::vector<std::shared_ptr<Node>> vertices;
	vertices.reserve(2 * edges.size());

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		vertices.push_back(x->Node0());
		vertices.push_back(x->Node1());
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
	if (NOT paired.second)
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
			vertices.push_back(x->Vtx0());
			vertices.push_back(x->Vtx1());
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
	const auto edges = Edges();
	const auto unMergedNodes = ::tnbLib::RetrieveNodes(edges);
	std::cout << "nb of  unMergedNodes: " << unMergedNodes.size() << std::endl;
	auto b = ::tnbLib::CalcBoundingBox(unMergedNodes);
	const auto d = b.Diameter();

	b.OffSet(1.0E-3*d);

	Geo_PrTree<std::shared_ptr<Node>> engine;
	engine.SetGeometryCoordFunc([](const std::shared_ptr<Node>& v)-> const Pnt3d& {Debug_Null_Pointer(v); return v->Coord(); });
	engine.SetGeometryRegion(b);

	const auto dp = Pnt3d(Radius(), Radius(), Radius());

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

			if (minDist <= Tolerance())
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
	std::cout << "nb of nodes: " << nodes.size() << std::endl;
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
		Debug_Null_Pointer(x);
		auto n0 = FindNode(x->Vtx0());
		auto n1 = FindNode(x->Vtx1());

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edgePaired = MergeSegments::MakeNewEdge(n0, n1);
		if (edgePaired.second)
		{
			auto& newEdge = edgePaired.first;

			newEdge->ImportToEdges(x);

			n0->ImportToEdges(newEdge);
			n1->ImportToEdges(newEdge);

			newEdge->SetIndex(++nbEdges);

			theMergedEdges_.push_back(std::move(newEdge));
		}
		else
		{
			auto& edge = edgePaired.first;
			edge->ImportToEdges(x);

			theMergedEdges_.push_back(std::move(edge));
		}
	}
}

void tnbLib::MergeSegments::Perform()
{
	Debug_If_Condition(theRadius_ < theTol_);

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
	const std::shared_ptr<Node>& theNode1
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
		auto edge = std::make_shared<Edge>(0, theNode0, theNode1);
		auto t = std::make_pair(std::move(edge), Standard_True);
		return std::move(t);
	}

	if (theNode1->IsOrphan())
	{
		auto edge = std::make_shared<Edge>(0, theNode0, theNode1);
		auto t = std::make_pair(std::move(edge), Standard_True);
		return std::move(t);
	}

	if (auto edge = CommonEdge(theNode0, theNode1))
	{
		auto t = std::make_pair(std::move(edge), Standard_False);
		return std::move(t);
	}

	auto edge = std::make_shared<Edge>(0, theNode0, theNode1);
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

			if (ed->Node0() IS_EQUAL theNode1)
			{
				return std::move(ed);
			}

			if (ed->Node1() IS_EQUAL theNode1)
			{
				return std::move(ed);
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
			vertices.push_back(std::move(vertex));
		}
		return std::move(vertices);
	}

	auto CreateSegments(const std::vector<std::shared_ptr<MergeSegments::Edge>>& edges)
	{
		Standard_Integer nbSegments = 0;

		std::vector<std::shared_ptr<TModel_Paired>> segments;
		segments.reserve(edges.size());
		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x);

			auto seg = std::make_shared<TModel_Paired>(++nbSegments, x->Edge0(), x->Edge1());
			segments.push_back(std::move(seg));
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

			auto ed0 = x->Edge0();
			auto ed1 = x->Edge1();

			if (NOT ed0)
			{
				FatalErrorIn("void LinkEdges(const entityManager_ptr& theEdges)")
					<< "Null pointer has been detected!" << endl
					<< abort(FatalError);
			}

			if (ed1)
			{
				ed0->SetPairedEdge(ed1);
				ed1->SetPairedEdge(ed0);
			}
		}
	}
}

void tnbLib::Cad_SolidMaker::Perform()
{
	if (theRadius_ < theTol_) std::swap(theTol_, theRadius_);

	const auto surfaces = Cad_Tools::GetSurfaces(Shape());
	std::cout << "nb of surfaces: " << surfaces.size() << std::endl;
	auto solid = std::make_shared<Cad_TModel>();
	Debug_Null_Pointer(solid);
	std::cout << Cad_Tools::RetrieveEdges(surfaces).size() << std::endl;
	auto edges = Cad_Tools::RetrieveEdges(surfaces);
	auto mergeAlg = std::make_shared<MergeSegments>(edges, theTol_, theRadius_);
	Debug_Null_Pointer(mergeAlg);

	mergeAlg->Perform();
	Debug_If_Condition_Message(NOT mergeAlg->IsDone(), "the algorithm is not performed");

	const auto& mergedEdges = mergeAlg->MergedEdges();
	const auto mergedNodes = MergeSegments::RetrieveNodes(mergedEdges);

	auto vertices = CreateVertices(mergedNodes);
	auto cornerManager = MakeCornerManager(vertices);

	SetCornerManager(std::move(cornerManager), solid);

	auto segments = CreateSegments(mergedEdges);
	auto segmentManagr = MakeSegmentManager(segments);

	SetSegmentManager(std::move(segmentManagr), solid);

	auto faceManager = MakeFaceManager(surfaces);

	SetFaceManager(std::move(faceManager), solid);

	LinkEdges(solid->Segments());

	solid->SetShape(Shape());

	theSolid_ = std::move(solid);

	Change_IsDone() = Standard_True;
}
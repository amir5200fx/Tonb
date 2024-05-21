#include <Aft3d_Volume.hxx>

#include <Aft3d_Tools.hxx>
#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_TopoTriangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::frontHandler::IsOnCurrentLevel
(
	const std::shared_ptr<Aft3d_Facet>& theFront
) const
{
	if (theFront->Node0()->Index() <= MaxId())
	{
		return Standard_False;
	}
	if (theFront->Node1()->Index() <= MaxId())
	{
		return Standard_False;
	}
	if (theFront->Node2()->Index() <= MaxId())
	{
		return Standard_False;
	}
	return Standard_True;
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMeshNodes
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	element.Node0()->InsertElement(theElement);
	element.Node1()->InsertElement(theElement);
	element.Node2()->InsertElement(theElement);
	element.Node3()->InsertElement(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMeshNodes
(
	const std::shared_ptr<Aft3d_Facet>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	element.Node0()->InsertFacet(theElement);
	element.Node1()->InsertFacet(theElement);
	element.Node2()->InsertFacet(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMeshNodes
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	edge.Node0()->InsertEdge(theEdge);
	edge.Node1()->InsertEdge(theEdge);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMeshEdges
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	facet.Edge0()->InsertFacet(theFacet);
	facet.Edge1()->InsertFacet(theFacet);
	facet.Edge2()->InsertFacet(theFacet);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMeshEdges
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	element.Edge0()->InsertElement(theElement);
	element.Edge1()->InsertElement(theElement);
	element.Edge2()->InsertElement(theElement);
	element.Edge3()->InsertElement(theElement);
	element.Edge4()->InsertElement(theElement);
	element.Edge5()->InsertElement(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMesh
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	AttachToMeshEdges(theFacet);
	AttachToMeshNodes(theFacet);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToMesh
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	AttachToMeshEdges(theElement);
	AttachToMeshNodes(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToFrontNodes
(
	const std::shared_ptr<Aft3d_Facet>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	element.Node0()->InsertFrontFacet(theElement);
	element.Node1()->InsertFrontFacet(theElement);
	element.Node2()->InsertFrontFacet(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToFrontNodes
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	edge.Node0()->InsertFrontEdge(theEdge);
	edge.Node1()->InsertFrontEdge(theEdge);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToFrontEdges
(
	const std::shared_ptr<Aft3d_Facet>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	element.Edge0()->InsertFront(theElement);
	element.Edge1()->InsertFront(theElement);
	element.Edge2()->InsertFront(theElement);
}

void tnbLib::legLib::Aft3d_VolumeCore::AttachToFronts
(
	const std::shared_ptr<Aft3d_Facet>& theFront
)
{
	AttachToFrontEdges(theFront);
	AttachToFrontNodes(theFront);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromMesh
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	if (NOT facet.IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< " Trying to delete a non-orphan facet!"
			<< abort(FatalError);
	}

	deAttachFromMeshEdges(theFacet);
	deAttachFromMeshNodes(theFacet);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromMesh
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	if (!edge.IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< " Trying to delete a non-orphan edge!"
			<< abort(FatalError);
	}

	edge.Node0()->RemoveEdge(theEdge);
	edge.Node1()->RemoveEdge(theEdge);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromMeshNodes
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	facet.Node0()->RemoveFacet(theFacet);
	facet.Node1()->RemoveFacet(theFacet);
	facet.Node2()->RemoveFacet(theFacet);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromMeshEdges
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	facet.Edge0()->RemoveFacet(theFacet);
	facet.Edge1()->RemoveFacet(theFacet);
	facet.Edge2()->RemoveFacet(theFacet);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromFronts
(
	const std::shared_ptr<Aft3d_Facet>& theFront
)
{
	deAttachFromFrontEdges(theFront);
	deAttachFromFrontNodes(theFront);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromFronts
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	edge.Node0()->RemoveFrontEdge(theEdge);
	edge.Node1()->RemoveFrontEdge(theEdge);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromFrontNodes
(
	const std::shared_ptr<Aft3d_Facet>& theFront
)
{
	Debug_Null_Pointer(theFront);
	auto& front = *theFront;

	front.Node0()->RemoveFrontFacet(theFront);
	front.Node1()->RemoveFrontFacet(theFront);
	front.Node2()->RemoveFrontFacet(theFront);
}

void tnbLib::legLib::Aft3d_VolumeCore::deAttachFromFrontEdges
(
	const std::shared_ptr<Aft3d_Facet>& theFront
)
{
	Debug_Null_Pointer(theFront);
	auto& front = *theFront;

	front.Edge0()->RemoveFront(theFront);
	front.Edge1()->RemoveFront(theFront);
	front.Edge2()->RemoveFront(theFront);
}

Standard_Integer 
tnbLib::legLib::Aft3d_Volume::Meshing()
{
	if (base::FrontHandler.Fronts().IsPriorityEmpty())
	{
		FatalErrorIn(FunctionSIG)
			<< "empty priority list detected!" << endl
			<< abort(FatalError);
	}

	base::FrontHandler.SetCurrentLev(0);
	base::FrontHandler.SetMaxLevel(base::Mesh.NbNodes());

	base::CycleInfo.SetCycleMode(cycleMode::generation);

	while (NOT base::FrontHandler.Fronts().IsPriorityEmpty())
	{
		MeshOneLevel();

		if (base::IsSameLevelSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::generation);
			continue;
		}

		if (base::IsCavityRemoverSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::repair);
		}

		base::FrontHandler.SetCurrentLev(base::FrontHandler.LevelNumber() + 1);

		if (base::FrontHandler.LevelNumber() >= theALLOWED_MAX_LEVEL_)
		{
			return 1;
		}

		if (base::IsNextLevelSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::generation);
		}
	}
	return 0;
}

void tnbLib::legLib::Aft3d_Volume::MeshOneLevel()
{
	base::ModifyLocalFront(DEFAULT_LOCALFRONT_FACTOR);

	while (base::GetCurrent())
	{
		std::vector<std::shared_ptr<Aft3d_Node>>
			candidates,
			localNodes;
		std::vector<std::shared_ptr<Aft3d_Facet>>
			effectives,
			locals;
		if (NOT base::IsBelongToFront())
		{
			continue;
		}

		// remove the current from the front [3/1/2023 Payvand]
		base::RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		base::CalcElementSize();

		// Calculate optimum coordinate of new point
		base::CalcOptimumCoord();

		base::CalcLocalFrontRadius();

		// Set depth of searching radius
		base::SetSearchingDepth();

		base::RetrieveLocalFrontNodes(localNodes, candidates);

		base::RetrieveLocalFrontEntities(localNodes, locals);

		base::RetrieveEffectiveFronts(locals, effectives);

		base::SortNodes(candidates);

		if (base::IsNewNodeValid(effectives))
		{
			base::AddOptimumNodeTo(candidates);
		}

		FindValidNode(candidates, effectives);

		UpdateFront();
	}
}

void tnbLib::legLib::Aft3d_Volume::FindValidNode
(
	const std::vector<std::shared_ptr<Aft3d_Node>>& theCandidates, 
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theEffectives
)
{
	static const Standard_Real AngleCriterion = 1.0 * PI / 180.0;
	Debug_Null_Pointer(CycleInfo.Current());
	Debug_Null_Pointer(CycleInfo.TempNode());
	Debug_Null_Pointer(MetricMap());
	const auto& current = *CycleInfo.Current();
	const auto& newNode = CycleInfo.TempNode();

	const auto cLength = current.CharLength();
	const auto& sizeMap = *MetricMap();

	const auto& node0 = current.Node0();
	const auto& node1 = current.Node1();
	const auto& node2 = current.Node2();

	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);
	Debug_Null_Pointer(node2);

	const auto& P0 = node0->Coord();
	const auto& P1 = node1->Coord();
	const auto& P2 = node2->Coord();

	const auto v0 = node0->Index();
	const auto v1 = node1->Index();
	const auto v2 = node2->Index();

	const auto minDisFactor = this->MinDistFactor() * cLength;
	const auto minDisFactorSq = minDisFactor * minDisFactor;

	// Retrieve the effective nodes [1/17/2023 Payvand]
	auto nodes =
		Aft3d_Tools::RetrieveNodes(theEffectives);

	auto segments = Aft3d_Tools::RetrieveEdges(theEffectives);

#ifdef FindValidNode_DEBUG
	std::vector<std::pair<Standard_Integer, word>> flags;
#endif // FindValidNode_DEBUG

	Standard_Integer flag = 0;
	for (const auto& x : theCandidates)
	{
		Debug_Null_Pointer(x);
		const auto& node = *x;

		const auto nodeId = node.Index();
		if ((nodeId IS_EQUAL v0) OR(nodeId IS_EQUAL v1) OR(nodeId IS_EQUAL v2))
		{
#ifdef FindValidNode_DEBUG
			auto paired = std::make_pair(x->Index(), "own");
			flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
			continue;
		}

		// test1: is the new point on the left side of the front [1/2/2023 Payvand]
		if (Geo_Tools::Oriented_cgal(node.Coord(), P0, P1, P2) <= 0.0)
		{
#ifdef FindValidNode_DEBUG
			auto paired = std::make_pair(x->Index(), "oriented");
			flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
			continue;
		}

		flag = 0;

		// test 2: intersection test [1/2/2023 Payvand]
		for (const auto& eff : theEffectives)
		{
			Debug_Null_Pointer(eff);

			const auto& n0 = eff->Node0();
			const auto& n1 = eff->Node1();
			const auto& n2 = eff->Node2();

			if (NOT Geo_Tools::IsOneCommonPointTwoTriangles(v0, v1, nodeId, n0->Index(), n1->Index(), n2->Index()))
			{
				if (Geo_Tools::IsIntersectionTwoTriangles_cgal(node0->Coord(), node1->Coord(), node.Coord(), n0->Coord(), n1->Coord(), n2->Coord()))
				{
					flag = 1;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "intersection");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (NOT Geo_Tools::IsOneCommonPointTwoTriangles(v1, v2, nodeId, n0->Index(), n1->Index(), n2->Index()))
			{
				if (Geo_Tools::IsIntersectionTwoTriangles_cgal(node1->Coord(), node2->Coord(), node.Coord(), n0->Coord(), n1->Coord(), n2->Coord()))
				{
					flag = 1;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "intersection");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (NOT Geo_Tools::IsOneCommonPointTwoTriangles(v2, v0, nodeId, n0->Index(), n1->Index(), n2->Index()))
			{
				if (Geo_Tools::IsIntersectionTwoTriangles_cgal(node2->Coord(), node0->Coord(), node.Coord(), n0->Coord(), n1->Coord(), n2->Coord()))
				{
					flag = 1;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "intersection");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}
		}

		if (flag) continue;

		for (const auto& n : nodes)
		{
			Debug_Null_Pointer(n);
			const auto n_indx = n->Index();

			if (n_indx IS_EQUAL nodeId) continue;
			if (n_indx IS_EQUAL v0) continue;
			if (n_indx IS_EQUAL v1) continue;
			if (n_indx IS_EQUAL v2) continue;

			if (Geo_Tools::IsPointInsideTetrahedron_cgal(n->Coord(), P0, P1, P2, node.Coord()))
			{
				flag = 2;
#ifdef FindValidNode_DEBUG
				auto paired = std::make_pair(x->Index(), "inside");
				flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
				break;
			}
		}

		if (flag) continue;

		if ((x NOT_EQUAL newNode) AND CheckAngle(current, node, AngleCriterion))
		{
			flag = 3;
#ifdef FindValidNode_DEBUG
			auto paired = std::make_pair(x->Index(), "angle");
			flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
			continue;
		}

		// Checking the distance between the effective nodes and the new triangles [1/17/2023 Payvand]
		for (const auto& n : nodes)
		{
			if (IsNewFace(node0, node1, x))
			{
				if (Geo_Tools::CalcSquareDistancePointFromTriangle_cgal(n->Coord(), P0, P1, x->Coord()) < minDisFactorSq)
				{
					flag = 4;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. PT dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (IsNewFace(node1, node2, x))
			{
				if (Geo_Tools::CalcSquareDistancePointFromTriangle_cgal(n->Coord(), P1, P2, x->Coord()) < minDisFactorSq)
				{
					flag = 4;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. PT dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (IsNewFace(node2, node0, x))
			{
				if (Geo_Tools::CalcSquareDistancePointFromTriangle_cgal(n->Coord(), P2, P0, x->Coord()) < minDisFactorSq)
				{
					flag = 4;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. PT dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}
		}

		if (flag) continue;

		// Checking the distance between the effective segments and the new segments [1/17/2023 Payvand]
		for (const auto& seg : segments)
		{
			Debug_Null_Pointer(seg);

			if (IsNewSegment(node0, x))
			{
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P0, x->Coord(), Aft3d_Tools::GetCoord0(*seg), Aft3d_Tools::GetCoord1(*seg)) < minDisFactorSq)
				{
					flag = 5;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. EE dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (IsNewSegment(node1, x))
			{
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P1, x->Coord(), Aft3d_Tools::GetCoord0(*seg), Aft3d_Tools::GetCoord1(*seg)) < minDisFactorSq)
				{
					flag = 5;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. EE dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}

			if (IsNewSegment(node2, x))
			{
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P2, x->Coord(), Aft3d_Tools::GetCoord0(*seg), Aft3d_Tools::GetCoord1(*seg)) < minDisFactorSq)
				{
					flag = 5;
#ifdef FindValidNode_DEBUG
					auto paired = std::make_pair(x->Index(), "min. EE dis");
					flags.push_back(std::move(paired));
#endif // FindValidNode_DEBUG
					break;
				}
			}
		}

		if (flag) continue;

		// All tests has been done and the node is accepted. [1/15/2023 Payvand]
		CycleInfo.SetValidNode(x);
		return;
	}
}

void tnbLib::legLib::Aft3d_Volume::UpdateFront()
{
	Debug_Null_Pointer(CycleInfo.ValidNode());
	const auto& node = *CycleInfo.ValidNode();

	CycleInfo.SetNodeMode(nodeMode::pickedUp);

	// check for updating the nodes tree
	if (node.Index() IS_EQUAL Counter.NbNodes() + 1)
	{
		Counter.NbNodes()++;

		CycleInfo.SetNodeMode(nodeMode::newPoint);

		// insert the new node into the NODES TREE
		theEngine_->InsertToGeometry(CycleInfo.ValidNode());
	}

	SetPairs();

	UpdatePairs();

	CreateElement();

	UpdateElement();

	RemoveEntitiesFromGeometry();

	RegisterElement();
}

void tnbLib::legLib::Aft3d_Volume::Import(const Entity3d_Triangulation& theVolume)
{
	const auto topo_mesh = std::make_shared<Entity3d_TopoTriangulation>(theVolume);
	Mesh.MaxNodeIdxRef() = theVolume.NbPoints();
	Mesh.MaxEdgeIdxRef() = topo_mesh->NbSegments();
	Mesh.MaxElementIdxRef() = theVolume.NbConnectivity();
	Mesh.MaxElementIdxRef() = 0;

	// Creating the boundaries
	CreateBoundary(*topo_mesh);

	// Retrieving the nodes
	const auto nodes = Aft3d_Tools::RetrieveNodes(*theBoundary_);
	// Retrieving the edges
	auto edges = Aft3d_Tools::RetrieveEdges(*theBoundary_);
	// computing the dimension of the region
	const auto region = Geo_BoxTools::GetBox(Aft3d_Tools::RetriveGeometries(nodes), 0);
	// Set searching the region
	EngineRef() = std::make_shared<Geo_AdTree<std::shared_ptr<Aft3d_Node>>>();
	Engine()->SetGeometryCoordFunc([](const std::shared_ptr<Aft3d_Node>& node)-> const Pnt3d& {return node->Coord(); });
	Engine()->SetGeometryRegion(region.Expanded(region.Diameter() * 1.e-3));
	// registering the nodes
	Engine()->InsertToGeometry(nodes);
	// creating the front
	FrontHandler.InsertToFronts(*theBoundary_);
	//.
	// The triangulation has been successfully imported.
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Volume::IsNewFace
(
	const std::shared_ptr<Aft3d_Node>& theV0,
	const std::shared_ptr<Aft3d_Node>& theV1, 
	const std::shared_ptr<Aft3d_Node>& theV2
)
{
	std::set<Standard_Integer> cmnFacets;
	{// Retrieve the common facets between node v0 and node v1 [1/17/2023 Payvand]
		std::set<Standard_Integer> reg;
		// Retrieve the front facets and register all of them into a set [1/17/2023 Payvand]
		for (const auto& x : theV0->FrontFacets())
		{
			auto f = x.second.lock();
			Debug_Null_Pointer(f);

			if (NOT reg.insert(f->Index()).second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected!" << endl
					<< abort(FatalError);
			}
		}

		// Retrieve the front facets of the node v2 [1/17/2023 Payvand]
		for (const auto& x : theV1->FrontFacets())
		{
			auto f = x.second.lock();
			Debug_Null_Pointer(f);

			if (NOT reg.insert(f->Index()).second)
			{
				// found a common front facet between node v0 and node v1. 
				// Putting them into a list [1/17/2023 Payvand]
				cmnFacets.insert(f->Index());
			}
		}
	}
	// the list is empty. So, no existing facet is detected. [1/17/2023 Payvand]
	if (cmnFacets.empty())
	{
		return Standard_False;
	}
	// For any front facets around the node, v2, if it was a facet 
	// that wasn't pushed into the list, then we have the existing facet between the nodes. [1/17/2023 Payvand]
	for (const auto& x : theV2->FrontFacets())
	{
		auto f = x.second.lock();
		Debug_Null_Pointer(f);

		if (NOT cmnFacets.insert(f->Index()).second)
		{
			// Found the common facet [1/17/2023 Payvand]
			return Standard_False;
		}
	}
	// no common facet has been detected; It's a new facet [1/17/2023 Payvand]
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Volume::IsNewSegment
(
	const std::shared_ptr<Aft3d_Node>& theV0,
	const std::shared_ptr<Aft3d_Node>& theV1
)
{
	std::set<Standard_Integer> cmnSegts;
	for (const auto& x : theV0->FrontEdges())
	{
		auto e = x.second.lock();
		if (NOT cmnSegts.insert(e->Index()).second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected." << endl
				<< abort(FatalError);
		}
	}
	for (const auto& x : theV1->FrontEdges())
	{
		auto e = x.second.lock();
		if (NOT cmnSegts.insert(e->Index()).second)
		{
			// Found the common segment [1/17/2023 Payvand]
			return Standard_False;
		}
	}
	// no common segment has been found. [1/17/2023 Payvand]
	return Standard_True;
}
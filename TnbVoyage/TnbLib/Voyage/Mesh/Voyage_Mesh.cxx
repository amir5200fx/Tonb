#include <Voyage_Mesh.hxx>

#include <VoyageMesh_Element.hxx>
#include <VoyageMesh_RefNode.hxx>
#include <Aft_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_Tools.hxx>

template<>
void tnbLib::VoyageMesh_Core::ModifyLocalFront(const Standard_Real theFactor)
{
	if (theFactor < (Standard_Real)1.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Factor"
			<< abort(FatalError);
	}

	if (frontData::IsGeometryEmpty())
	{
		return;
	}

	Debug_Null_Pointer(base::MetricMap());
	const auto& sizeMap = *base::MetricMap();

	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	frontData::RetrieveFromGeometryTo(nodes);

	for (auto& ptr : nodes)
	{
		Debug_Null_Pointer(ptr);
		auto& node = *ptr;
		const auto& pt = node.Coord();
		auto fronts = node.RetrieveFrontEdges();
		Debug_If_Condition(NOT fronts.size());

		//- Retrieve max_length attached to the current node
		Standard_Real maxLength = (Standard_Real)0.;
		for (auto& w_entity : fronts)
		{
			Debug_Null_Pointer(w_entity.second.lock());
			auto entity = w_entity.second.lock();

			if (entity->CharLength() > maxLength)
				maxLength = entity->CharLength();
		}

		//- Retrieve worst metric attached to the current node
		auto Iter = fronts.begin();
		auto M = Iter->second.lock()->EffectiveMetric();
		Iter++;

		while (Iter NOT_EQUAL fronts.end())
		{
			const auto& Mi = Iter->second.lock()->EffectiveMetric();
			//Mi.Print(std::cout);
			//std::cout << std::endl;
			if (M.Determinant() < Mi.Determinant())
			{
				M = Entity2d_Metric1::UnionSR(M, Mi);
			}
			else
			{
				M = Entity2d_Metric1::UnionSR(Mi, M);
			}
			Iter++;
		}

		maxLength *= theFactor;
		Debug_If_Condition_Message
		(
			maxLength <= (Standard_Real)0.,
			" Invalid MaxLength Value"
		);

		//- save the max_length
		node.SetRadius
		(
			MAX(node.Radius(), maxLength)
		);

		auto detM = M.Determinant();

		//- save worst metric
		if (node.Metric().Determinant() < detM)
		{
			node.SetMetric(Entity2d_Metric1::UnionSR(node.Metric(), M));
		}
		else
		{
			node.SetMetric(Entity2d_Metric1::UnionSR(M, node.Metric()));
		}

		//auto h = sizeMap.CalcElementSize(node.Coord());

		std::vector<std::shared_ptr<VoyageMesh_Node>> locals;
		frontData::GeometrySearch
		(
			sizeMap.CalcSearchRegion(MAX(maxLength, sizeMap.CalcElementSize(node.Coord())), M, node.Coord()),
			locals
		);

		std::vector<std::shared_ptr<VoyageMesh_Node>> inners;
		base::NodesInRadius
		(
			maxLength,
			node.Coord(),
			locals,
			inners
		);

		for (auto& innerNode : inners)
		{
			innerNode->SetRadius
			(
				MAX(innerNode->Radius(), maxLength)
			);

			if (innerNode->Metric().Determinant() < detM)
			{
				innerNode->SetMetric(Entity2d_Metric1::UnionSR(innerNode->Metric(), M));
			}
			else
			{
				innerNode->SetMetric(Entity2d_Metric1::UnionSR(M, innerNode->Metric()));
			}
		}
	}
}

void tnbLib::Voyage_Mesh::MeshOneLevel()
{
	ModifyLocalFront(DEFAULT_LOCALFRONT_FACTOR);

	while (GetFrontEntity())
	{
		std::vector<std::shared_ptr<VoyageMesh_Node>>
			CandidateNodes,
			LocalNodes;

		std::vector<std::shared_ptr<VoyageMesh_Edge>>
			Effectives,
			Local;

		if (NOT IsBelongToFront())
			continue;

		// Remove the Current from front
		RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		CalcElementSize();
		
		std::cout <<" elm no. "<< this->NbElements() + 1 << ", element size: " << this->ElementSize() << std::endl;
		// Calculate optimum coordinate of new point
		CalcOptimumCoord();

		CalcLocalFrontRadius();

		// Set depth of searching radius
		SetDepthSearching();

		RetrieveLocalFrontNodes(LocalNodes, CandidateNodes);

		//RetrieveLocalFrontEntities(LocalNodes, Local);

		RetrieveEffectiveFronts(Local, Effectives);

		SortNodes(CandidateNodes);

		if (IsNewPointCandidate(Effectives))
		{
			AddOptimumNodeTo(CandidateNodes);
		}

		FindValidNode(CandidateNodes, Effectives);

		Update();
	}
}

void tnbLib::Voyage_Mesh::FindValidNode
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theCandidates, 
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	Debug_Null_Pointer(CurrentFront());
	const auto& current = *CurrentFront();
	const auto& newNode = TempoNode();

	const auto cLength = current.CharLength();
	const auto& sizeMap = *MetricMap();

	Debug_Null_Pointer(current.Node0());
	Debug_Null_Pointer(current.Node1());

	const auto& vrtx0 = *current.Node0();
	const auto& vrtx1 = *current.Node1();

	auto v0 = vrtx0.Index();
	auto v1 = vrtx1.Index();

	auto nodes = RetrieveNodesFrom(theEdges);

	Standard_Integer flag = 0;
	for (const auto& x : theCandidates)
	{
		Debug_Null_Pointer(x);
		const auto& node = *x;

		const auto nodeIndex = node.Index();
		if ((nodeIndex IS_EQUAL v0) OR(nodeIndex IS_EQUAL v1))
		{
			continue;
		}

		// test 1: is it the new point on the left side of iEDG
		if (Geo_Tools::Oriented_cgal(node.Coord(), vrtx0.Coord(), vrtx1.Coord()) <= 0.0)
		{
			continue;
		}

		flag = 0;

		// test 2: intersection test
		for (const auto& eff_ptr : theEdges)
		{
			Debug_Null_Pointer(eff_ptr);
			const auto& effective = *eff_ptr;

			const auto& n0 = *effective.Node0();
			const auto& n1 = *effective.Node1();

			if (NOT Geo_Tools::IsOneCommonPointTwoSegments(v0, nodeIndex, n0.Index(), n1.Index()))
			{
				if (Geo_Tools::HasIntersection_cgal(vrtx0.Coord(), node.Coord(), n0.Coord(), n1.Coord()))
				{
					flag = 1;
					break;
				}
			}

			if (NOT Geo_Tools::IsOneCommonPointTwoSegments(nodeIndex, v1, n0.Index(), n1.Index()))
			{
				if (Geo_Tools::HasIntersection_cgal(node.Coord(), vrtx1.Coord(), n0.Coord(), n1.Coord()))
				{
					flag = 1;
					break;
				}
			}
		}

		if (flag) continue;

		for (const auto& eff_node : nodes)
		{
			Debug_Null_Pointer(eff_node);
			const auto eff_index = eff_node->Index();

			if ((eff_index NOT_EQUAL nodeIndex) AND(eff_index NOT_EQUAL v0) AND(eff_index NOT_EQUAL v1))
			{
				if (Geo_Tools::IsPointInsideTriangle_cgal(eff_node->Coord(), vrtx0.Coord(), vrtx1.Coord(), node.Coord()))
				{
					flag = 2;
					break;
				}
			}
		}

		if (flag) continue;

		if ((x NOT_EQUAL newNode))
		{
			flag = 3;
			continue;
		}

		SetValidNode(x);
		return;
	}
	SetValidNode(nullptr);
}


void tnbLib::Voyage_Mesh::Update()
{
	if (ValidNode())
	{
		UpdateFront();
		InsertNewFrontsToLevels();
	}
	else
	{
		RejectCurrent(CurrentFront());
	}
}

void tnbLib::Voyage_Mesh::Mesh()
{
	if (IsPriorityEmpty())
	{
		FatalErrorIn(FunctionSIG)
			<< "Empty priority list" << endl
			<< abort(FatalError);
	}
	SetLevelNumber(0);
	SetLevelMaxIndex(NodeCounter());

	AlgCondition() = Aft_AlgCondition::Generation;

	MeshOneLevel();
}

void tnbLib::Voyage_Mesh::InsertNewFrontsToLevels()
{
	const auto& edge0 = CreatedEdge0();
	if (edge0)
	{
		const auto& n0 = edge0->Node0();
		const auto& n1 = edge0->Node1();

		n0->SetRadius(MAX(n0->Radius(), edge0->CharLength()));
		n1->SetRadius(MAX(n1->Radius(), edge0->CharLength()));

		if (IsOnLevel(*edge0))
		{
			InsertToCurrentFronts(edge0->Index(), edge0);
		}
		else
		{
			InsertToNextFronts(edge0->Index(), edge0);
		}
	}

	const auto& edge1 = CreatedEdge1();
	if (edge1)
	{
		const auto& n0 = edge1->Node0();
		const auto& n1 = edge1->Node1();

		n0->SetRadius(MAX(n0->Radius(), edge1->CharLength()));
		n1->SetRadius(MAX(n1->Radius(), edge1->CharLength()));

		if (IsOnLevel(*edge1))
		{
			InsertToCurrentFronts(edge1->Index(), edge1);
		}
		else
		{
			InsertToNextFronts(edge1->Index(), edge1);
		}
	}
}

void tnbLib::Voyage_Mesh::CheckPath
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
) const
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());

		auto n0 = std::dynamic_pointer_cast<VoyageMesh_RefNode>(x->Node0());
		auto n1 = std::dynamic_pointer_cast<VoyageMesh_RefNode>(x->Node1());
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		if (n0->IsArrival() OR n0->IsDeparture())
		{
			// do nothing [9/3/2023 Payvand]
		}
		else
		{
			if (n0->NbFrontEdges() NOT_EQUAL 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "The edge is not manifold" << endl
					<< " - n0 size: " << n0->NbFrontEdges() << endl
					<< " - n1 size: " << n1->NbFrontEdges() << endl
					<< abort(FatalError);
			}
		}
		if (n1->IsArrival() OR n1->IsDeparture())
		{
			// do nothing [9/3/2023 Payvand]
		}
		else
		{
			if (n1->NbFrontEdges() NOT_EQUAL 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "The edge is not manifold" << endl
					<< " - n0 size: " << n0->NbFrontEdges() << endl
					<< " - n1 size: " << n1->NbFrontEdges() << endl
					<< abort(FatalError);
			}
		}
		
	}
}

void tnbLib::Voyage_Mesh::CheckSelfIntersection() const
{
	for (const auto& x : RefPath())
	{
		Debug_Null_Pointer(x);

		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto radius = 1.05 * std::max(n0->CalcMaxParaAdjLength(), n1->CalcMaxParaAdjLength());
		const auto& c = x->Centre();

		auto b = Geo_BoxTools::GetBox(c, radius);

		std::vector<std::shared_ptr<VoyageMesh_Node>> items;
		this->GeometrySearch(b, items);

		std::vector<std::shared_ptr<VoyageMesh_Edge>> locals;
		RetrieveLocalFrontEntities(items, locals);

		for (const auto& l : locals)
		{
			Debug_Null_Pointer(l);
			if (x IS_EQUAL l) continue;
			if (Aft_Tools::IsIntersect(*x, *l))
			{
				FatalErrorIn(FunctionSIG)
					<< " a self intersection of the parametric boundary edges has been detected." << endl
					<< abort(FatalError);
			}
		}
	}
}

void tnbLib::Voyage_Mesh::InitFronts()
{
	Debug_Null_Pointer(MetricMap());
	const auto& sizeMap = *MetricMap();
	const auto& edges = RefPath();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		x->SetEffectiveMetric(sizeMap.CalcEffectiveMetric(n0->Coord(), n1->Coord()));
		x->SetCentre(sizeMap.CalcCentre(n0->Coord(), n1->Coord()));
		x->SetCharLength(sizeMap.CalcDistance(n0->Coord(), n1->Coord()));
	}
	auto nodes = RetrieveNodesFrom(edges);
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		const auto& bnds = x->RetrieveFrontEdges();
		auto Iter = bnds.begin();
		Debug_Null_Pointer(Iter->second.lock());
		auto M = Iter->second.lock()->EffectiveMetric();
		Iter++;

		while (Iter NOT_EQUAL bnds.end())
		{
			Debug_Null_Pointer(Iter->second.lock());
			const auto& Mi = Iter->second.lock()->EffectiveMetric();
			if (M.Determinant() < Mi.Determinant())
			{
				M = Entity2d_Metric1::UnionSR(M, Mi);
			}
			else
			{
				M = Entity2d_Metric1::UnionSR(Mi, M);
			}
			Iter++;
		}

		x->SetMetric(M);
	}
}

void tnbLib::Voyage_Mesh::ActiveFronts
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		n0->InsertToEdges(x->Index(), x);
		n1->InsertToEdges(x->Index(), x);

		n0->InsertToFrontEdges(x->Index(), x);
		n1->InsertToFrontEdges(x->Index(), x);
	}
}

void tnbLib::Voyage_Mesh::Perform()
{
	SetPriorityFunction(&Voyage_Mesh::Length);
	SetMinDistFactor(DEFAULT_MIN_DISTANCE_FACTOR);

	SetGeometryCoordFunc(&Voyage_Mesh::GetCoord);

	ActiveFronts(RefPath());

	Import(RefPath(), this->MetricMap());

	InitFronts();
	
	Mesh();

	Change_IsDone() = Standard_True;
}

void tnbLib::Voyage_Mesh::LoadRefPath
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsReference())
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not reference." << endl
				<< abort(FatalError);
		}
	}
	theRefPath_ = theEdges;
}

void tnbLib::Voyage_Mesh::LoadRefPath
(
	std::vector<std::shared_ptr<VoyageMesh_Edge>>&& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsReference())
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not reference." << endl
				<< abort(FatalError);
		}
	}
	theRefPath_ = std::move(theEdges);
}

void tnbLib::Voyage_Mesh::Import
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& thePath,
	const std::shared_ptr<VoyageMesh_MetricPrcsr>& theMetrics
)
{
	NodeCounter() = (Standard_Integer)(thePath.size() + 1);
	ElementCounter() = 0;
	EdgeCounter() = (Standard_Integer)thePath.size();

	CheckPath(RefPath());

	const auto nodes = RetrieveNodesFrom(RefPath());

	auto d = RetrieveBoundingBox(nodes);

	// Set Searching Region
	SetGeometryRegion(d.OffSet(0.01 * d.Diameter()));

	// Insert To Front
	InsertToGeometry(nodes);

	CheckSelfIntersection();

	InsertToPriority(RefPath());
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Node>> 
tnbLib::Voyage_Mesh::RetrieveNodesFrom
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	static auto cmp = 
		[]
	(
		const std::shared_ptr<VoyageMesh_Node>& n0,
		const std::shared_ptr<VoyageMesh_Node>& n1
		)
	{
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		return n0->Index() < n1->Index();
	};
	std::set<std::shared_ptr<VoyageMesh_Node>, decltype(cmp)> compct(cmp);
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());
		{
			auto insert = compct.insert(x->Node0());
			if (NOT insert.second)
			{
				// do nothing [8/22/2023 aamir]
			}
		}
		{
			auto insert = compct.insert(x->Node1());
			if (NOT insert.second)
			{
				// do nothing [8/22/2023 aamir]
			}
		}
	}
	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	std::copy(compct.begin(), compct.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

tnbLib::Entity2d_Box 
tnbLib::Voyage_Mesh::RetrieveBoundingBox
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes
)
{
	std::vector<Pnt2d> coords;
	coords.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		coords.push_back(x->Coord());
	}
	auto b = Entity2d_Box::BoundingBoxOf(coords);
	return std::move(b);
}

Standard_Real 
tnbLib::Voyage_Mesh::Length
(
	const std::shared_ptr<VoyageMesh_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	return theEdge->CharLength();
}

const tnbLib::Pnt2d& 
tnbLib::Voyage_Mesh::GetCoord
(
	const std::shared_ptr<VoyageMesh_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	return theNode->Coord();
}
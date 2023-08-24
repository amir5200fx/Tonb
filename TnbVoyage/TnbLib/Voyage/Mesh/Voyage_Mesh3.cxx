#include <Voyage_Mesh3.hxx>

#include <VoyageMesh_Element.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_Tools.hxx>

void tnbLib::Voyage_Mesh3::MeshOneLevel()
{
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

void tnbLib::Voyage_Mesh3::FindValidNode
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


void tnbLib::Voyage_Mesh3::Update()
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

void tnbLib::Voyage_Mesh3::InsertNewFrontsToLevels()
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

void tnbLib::Voyage_Mesh3::Perform()
{
	
}

std::vector<std::shared_ptr<tnbLib::VoyageMesh_Node>> 
tnbLib::Voyage_Mesh3::RetrieveNodesFrom
(
	const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<VoyageMesh_Node>& n0, const std::shared_ptr<VoyageMesh_Node>& n1)
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
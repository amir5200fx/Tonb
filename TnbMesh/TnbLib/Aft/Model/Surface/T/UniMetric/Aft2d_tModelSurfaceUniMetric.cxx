#include <Aft2d_tModelSurfaceUniMetric.hxx>

#include <Aft2d_EdgeSurface.hxx>

unsigned short tnbLib::Aft2d_tModelSurfaceUniMetric::verbose(0);

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::Import
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundary,
	const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theBoundaryMap
)
{
#ifdef AFT_MODEL_DEBUG
	NodeCounter() = (Standard_Integer)theBoundary.size();
	ElementCounter() = 0;
	EdgeCounter() = (Standard_Integer)theBoundary.size();

	CheckBoundary(GetBoundaryEntities());

	const auto& nodes = RetrieveNodesFrom(GetBoundaryEntities());

	auto box = RetrieveBoundingBox(nodes);

	// Set Searching Region
	SetGeometryRegion(box.OffSet(0.01 * box.Diameter()));

	// Insert To Front
	InsertToGeometry(nodes);
	InsertToPriority(GetBoundaryEntities());
#else
#include <Aft2d_Model_Import.jxx>
#endif // AFT_MODEL_DEBUG

}

namespace tnbLib
{
	Standard_Boolean CheckAngleSurfaceT
	(
		const Aft2d_EdgeSurface& theFront,
		const Aft2d_NodeSurface& theNode,
		const Aft2d_MetricPrcsrSurfaceUniMetric& theMetric,
		const Standard_Real CosAngle
	)
	{
#ifdef AFT_MODEL_DEBUG
		const auto clength = theFront.CharLength();

		const auto& vrtx0 = *theFront.Node0();
		const auto& vrtx1 = *theFront.Node1();

		const auto l0 = theMetric.CalcDistance(vrtx0.Coord(), theNode.Coord());
		const auto l1 = theMetric.CalcDistance(vrtx1.Coord(), theNode.Coord());

		const auto angN0 = (l0 * l0 + clength * clength - l1 * l1) / (2.0 * l0 * clength);
		if (NOT INSIDE(angN0, -CosAngle, CosAngle))
		{
			return Standard_True;
		}

		const auto angN1 = (l1 * l1 + clength * clength - l0 * l0) / (2.0 * l1 * clength);
		if (NOT INSIDE(angN1, -CosAngle, CosAngle))
		{
			return Standard_True;
		}
		return Standard_False;
#else
#include <Aft2d_Model_CheckAngles.jxx>
#endif // AFT_MODEL_DEBUG

	}
}

#ifdef AFT_MODEL_DEBUG
template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::MeshingOneLevel()
{
	if (verbose)
	{
		Info << " - Level nb. " << base::LevelNumber() << endl;
	}

	ModifyLocalFront(DEFAULT_LOCALFRONT_FACTOR);

	while (GetFrontEntity())
	{
		std::vector<std::shared_ptr<Aft2d_NodeSurface>>
			CandidateNodes,
			LocalNodes;

		std::vector<std::shared_ptr<Aft2d_EdgeSurface>>
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

		RetrieveLocalFrontEntities(LocalNodes, Local);

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
#endif // AFT_MODEL_DEBUG

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::FindValidNode
(
	const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theCandidates,
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEffectives
)
{
	Debug_Null_Pointer(base::CurrentFront());

	const auto& current = *base::CurrentFront();
	const auto& newNode = base::TempoNode();

	const auto cLength = current.CharLength();
	const auto& sizeMap = *base::MetricMap();

	Debug_Null_Pointer(current.Node0());
	Debug_Null_Pointer(current.Node1());

	const auto& vrtx0 = *current.Node0();
	const auto& vrtx1 = *current.Node1();

	auto v0 = vrtx0.Index();
	auto v1 = vrtx1.Index();

	auto nodes =
		RetrieveNodesFrom(theEffectives);

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
		for (const auto& eff_ptr : theEffectives)
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

		if ((x NOT_EQUAL newNode) AND CheckAngleSurfaceT(current, node, *base::MetricMap(), 0.998))
		{
			flag = 3;
			continue;
		}

		/*const auto l0 = sizeMap.CalcDistance(vrtx0.Coord(), node.Coord());
		const auto l1 = sizeMap.CalcDistance(vrtx1.Coord(), node.Coord());

		const auto angN0 = (l0*l0 + cLength * cLength - l1 * l1) / (2.0*l0*cLength);
		if (NOT INSIDE(angN0, -0.9986295, 0.9986295))
		{
			flag = 3;
			continue;
		}

		const auto angN1 = (l1*l1 + cLength * cLength - l0 * l0) / (2.0*l1*cLength);
		if (NOT INSIDE(angN1, -0.9986295, 0.9986295))
		{
			flag = 3;
			continue;
		}*/

		base::SetValidNode(x);
		return;
	}

	base::SetValidNode(nullptr);
}

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::InsertNewFrontsToLevels()
{
#ifdef AFT_MODEL_DEBUG
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
#else
#include <Aft2d_Model_InsertNewFrontsToLevels.jxx>
#endif // AFT_MODEL_DEBUG

}

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::CompactNumbering
(
	const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
) const
{
#include <Aft2d_Model_CompactNumbering.jxx>
}

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::ActiveFront
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
)
{
#include <Aft2d_Model_ActiveFront.jxx>
}

template<>
void tnbLib::Aft2d_tModelSurfaceUniMetric::CheckBoundary
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theFronts
)
{
#include <Aft2d_Model_CheckBoundary.jxx>
}
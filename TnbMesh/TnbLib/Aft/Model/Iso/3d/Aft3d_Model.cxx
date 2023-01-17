#include <Aft3d_Model.hxx>

#include <Aft2d_ElementSurface.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_Element.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_Edge.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>

template<>
void tnbLib::Aft3d_Model::Import
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theBoundaries,
	const std::shared_ptr<Aft3d_MetricPrcsr>& theBoundaryMap
)
{
	ElementCounter() = 0;

	const auto nodes = Aft_Tools::RetrieveNodes(theBoundaries);

	NodeCounter() = (Standard_Integer)nodes.size();
	EdgeCounter() = Aft_Tools::CalcNbEdges(theBoundaries);
	FacetCounter() = (Standard_Integer)theBoundaries.size();

	CheckBoundary(GetBoundaryEntities());

	const auto box = RetrieveBoundingBox(nodes);

	// Set Searching Region
	SetGeometryRegion(box.OffSet(0.01 * box.Diameter()));

	// Insert To Front
	InsertToGeometry(nodes);
	InsertToPriority(GetBoundaryEntities());
}

namespace tnbLib
{

	Standard_Boolean CheckAngle
	(
		const Aft3d_Facet& theFront,
		const Aft3d_Node& theNode, 
		const Standard_Real theAngle
	)
	{
		const auto& p0 = theFront.Node0()->Coord();
		const auto& p1 = theFront.Node1()->Coord();
		const auto& p2 = theFront.Node2()->Coord();

		// calculate the normal of the front [1/15/2023 Payvand]
		const auto n0 = Geo_Tools::CalcNormal(p0, p1, p2);
		
		{// checking the angle between the front and the first plane [1/15/2023 Payvand]
			const auto n1 = Geo_Tools::CalcNormal(p0, theNode.Coord(), p1);
			const auto angle = n0.Angle(n1);
			if (NOT INSIDE(angle, theAngle, PI - theAngle))
			{
				return Standard_True;
			}
		}

		{// checking the angle between the front and the second plane [1/15/2023 Payvand]
			const auto n1 = Geo_Tools::CalcNormal(p1, theNode.Coord(), p2);
			const auto angle = n0.Angle(n1);
			if (NOT INSIDE(angle, theAngle, PI - theAngle))
			{
				return Standard_True;
			}
		}

		{// checking the angle between the front and the third plane [1/15/2023 Payvand]
			const auto n1 = Geo_Tools::CalcNormal(p2, theNode.Coord(), p0);
			const auto angle = n0.Angle(n1);
			if (NOT INSIDE(angle, theAngle, PI - theAngle))
			{
				return Standard_True;
			}
		}
		// Everything is OK! [1/15/2023 Payvand]
		return Standard_False;
	}

	Standard_Boolean IsNewFacet
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
			for (const auto& x : theV0->RetrieveFrontFacets())
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
			for (const auto& x : theV1->RetrieveFrontFacets())
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
		for (const auto& x : theV2->RetrieveFrontFacets())
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

	Standard_Boolean IsNewSegment
	(
		const std::shared_ptr<Aft3d_Node>& theV0,
		const std::shared_ptr<Aft3d_Node>& theV1
	)
	{
		std::set<Standard_Integer> cmnSegts;
		for (const auto& x : theV0->RetrieveFrontEdges())
		{
			auto e = x.second.lock();
			if (NOT cmnSegts.insert(e->Index()).second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been detected." << endl
					<< abort(FatalError);
			}
		}
		for (const auto& x : theV1->RetrieveFrontEdges())
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
}

template<>
void tnbLib::Aft3d_Model::FindValidNode
(
	const std::vector<std::shared_ptr<Aft3d_Node>>& theCandidates,
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theEffectives
)
{
	static const Standard_Real AngleCriterion = 1.0 * PI / 180.0;
	Debug_Null_Pointer(this->CurrentFront());
	const auto& current = this->CurrentFront();
	const auto& newNode = this->TempoNode();

	const auto cLength = current->CharLength();
	const auto& sizeMap = this->MetricMap();

	const auto& node0 = current->Node0();
	const auto& node1 = current->Node1();
	const auto& node2 = current->Node2();

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
		RetrieveNodesFrom(theEffectives);

	std::vector<std::shared_ptr<Aft3d_Edge>> 
		segments = Aft_Tools::RetrieveEdges(theEffectives);

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

		if ((x NOT_EQUAL newNode) AND CheckAngle(*current, node, AngleCriterion))
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
			if (IsNewFacet(node0, node1, x))
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

			if (IsNewFacet(node1, node2, x))
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

			if (IsNewFacet(node2, node0, x))
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
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P0, x->Coord(), Aft_Tools::GetCoord0(*seg), Aft_Tools::GetCoord1(*seg)) < minDisFactorSq)
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
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P1, x->Coord(), Aft_Tools::GetCoord0(*seg), Aft_Tools::GetCoord1(*seg)) < minDisFactorSq)
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
				if (Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(P2, x->Coord(), Aft_Tools::GetCoord0(*seg), Aft_Tools::GetCoord1(*seg)) < minDisFactorSq)
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
		base::SetValidNode(x);
		return;
	}

	// No valid node is found [1/15/2023 Payvand]
	base::SetValidNode(nullptr);
}

template<>
void tnbLib::Aft3d_Model::InsertNewFrontsToLevels()
{
	{
		const auto& facet = this->CreatedFacet0();
		if (facet)
		{
			if (this->IsOnLevel(*facet))
			{
				this->InsertToCurrentFronts(facet->Index(), facet);
			}
			else
			{
				this->InsertToNextFronts(facet->Index(), facet);
			}
		}
	}

	{
		const auto& facet = this->CreatedFacet1();
		if (facet)
		{
			if (this->IsOnLevel(*facet))
			{
				this->InsertToCurrentFronts(facet->Index(), facet);
			}
			else
			{
				this->InsertToNextFronts(facet->Index(), facet);
			}
		}
	}

	{
		const auto& facet = this->CreatedFacet2();
		if (facet)
		{
			if (this->IsOnLevel(*facet))
			{
				this->InsertToCurrentFronts(facet->Index(), facet);
			}
			else
			{
				this->InsertToNextFronts(facet->Index(), facet);
			}
		}
	}

	{
		const auto& edge = this->CreatedEdge3();
		if (edge)
		{
			const auto& n0 = edge->Node0();
			const auto& n1 = edge->Node1();

			n0->SetRadius(std::max(n0->Radius(), edge->CharLength()));
			n1->SetRadius(std::max(n1->Radius(), edge->CharLength()));
		}
	}

	{
		const auto& edge = this->CreatedEdge4();
		if (edge)
		{
			const auto& n0 = edge->Node0();
			const auto& n1 = edge->Node1();

			n0->SetRadius(std::max(n0->Radius(), edge->CharLength()));
			n1->SetRadius(std::max(n1->Radius(), edge->CharLength()));
		}
	}

	{
		const auto& edge = this->CreatedEdge5();
		if (edge)
		{
			const auto& n0 = edge->Node0();
			const auto& n1 = edge->Node1();

			n0->SetRadius(std::max(n0->Radius(), edge->CharLength()));
			n1->SetRadius(std::max(n1->Radius(), edge->CharLength()));
		}
	}
}

template<>
void tnbLib::Aft3d_Model::CompactNumbering
(
	const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
) const
{
	std::vector<std::shared_ptr<Aft3d_Node>> nodes = Aft_Tools::RetrieveNodes(theElements);
	std::vector<std::shared_ptr<Aft3d_Edge>> edges = Aft_Tools::RetrieveEdges(theElements);
	std::vector<std::shared_ptr<Aft3d_Facet>> facets = Aft_Tools::RetrieveFacets(theElements);

	cache::NodesIndices = std::make_shared<typename cache::indexMap>();
	auto& nodeIndices = *cache::NodesIndices;
	cache::nodeIndex = 0;

	cache::EdgesIndices = std::make_shared<typename cache::indexMap>();
	auto& edgeIndices = *cache::EdgesIndices;
	cache::edgeIndex = 0;

	cache::FacetsIndices = std::make_shared<typename cache::indexMap>();
	auto& facetIndices = *cache::FacetsIndices;
	cache::facetIndex = 0;

	cache::ElementsIndices = std::make_shared<typename cache::indexMap>();
	auto& elementIndices = *cache::ElementsIndices;
	cache::elementIndex = 0;

	for (const auto& x : nodes)
	{
		auto paired = std::make_pair(x->Index(), ++cache::nodeIndex);
		nodeIndices.insert(std::move(paired));
	}

	for (const auto& x : edges)
	{
		auto paired = std::make_pair(x->Index(), ++cache::edgeIndex);
		edgeIndices.insert(std::move(paired));
	}

	for (const auto& x : facets)
	{
		auto paired = std::make_pair(x->Index(), ++cache::facetIndex);
		facetIndices.insert(std::move(paired));
	}

	for (const auto& x : theElements)
	{
		auto paired = std::make_pair(x->Index(), ++cache::elementIndex);
		elementIndices.insert(std::move(paired));
	}
}

template<>
void tnbLib::Aft3d_Model::ActiveFront
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
)
{
	for (const auto& x : theFronts)
	{
		Debug_Null_Pointer(x);
		auto [n0, n1, n2] = x->Nodes();

		n0->InsertToFacets(x->Index(), x);
		n1->InsertToFacets(x->Index(), x);
		n2->InsertToFacets(x->Index(), x);

		n0->InsertToFrontFacets(x->Index(), x);
		n1->InsertToFrontFacets(x->Index(), x);
		n2->InsertToFrontFacets(x->Index(), x);
	}

	std::vector<std::shared_ptr<Aft3d_Edge>> edges 
		= Aft_Tools::RetrieveEdges(theFronts);
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		n0->InsertToEdges(x->Index(), x);
		n1->InsertToEdges(x->Index(), x);

		n0->InsertToFrontEdges(x->Index(), x);
		n1->InsertToFrontEdges(x->Index(), x);
	}
}

template<>
void tnbLib::Aft3d_Model::CheckBoundary
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
)
{
	auto edges = Aft_Tools::RetrieveEdges(theFronts);
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		if (x->NbFacets() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "the front is not manifold!" << endl
				<< abort(FatalError);
		}
	}
}
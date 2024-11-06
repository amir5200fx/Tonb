#include <Aft3d_Volume.hxx>

#include <Aft3d_NodeCalculator.hxx>
#include <Aft3d_GeoPrcsr.hxx>
#include <Aft3d_Element.hxx>
#include <Aft3d_InteriorFacet.hxx>
#include <Aft3d_InteriorEdge.hxx>
#include <Aft3d_Node.hxx>
#include <Aft3d_InteriorNode.hxx>
#include <Aft3d_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::legLib::Aft3d_VolumeCore::SIZE_TO_HIGHT_ELEMENT_COEFF = 0.866025404;

tnbLib::legLib::Aft3d_VolumeCore::cavityFronts::cavityFronts()
	: theUncertainty_(cmp_facet)
	, theCertainty_(cmp_facet)
{
	// Empty body
}

void tnbLib::legLib::Aft3d_VolumeCore::meshData::Insert(const std::vector<std::shared_ptr<Aft3d_Element>>& theElements) const
{
	for (const auto& elm: theElements)
	{
		theElements_->insert(elm);
	}
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::GetCurrent()
{
	std::shared_ptr<Aft3d_Facet> current;
	auto got = FrontHandler.GetFront(current);
	if (NOT got)
	{
		return Standard_False;
	}

	CycleInfo.Reset();
	Debug_Null_Pointer(current);
	CycleInfo.SetCurrent(std::move(current));
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsBelongToFront() const
{
	Debug_Null_Pointer(CycleInfo.Current());
	return CycleInfo.Current()->IsOnFront();
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsNewNodeValid
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts
) const
{
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::repair)
	{
		return Standard_False;
	}
	Debug_Null_Pointer(Current());
	const auto factor = MinDistFactor();
	Debug_If_Condition(factor <= 0.0);

	const auto& coord = CycleInfo.Coord();
	for (const auto& x : theFronts)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		const auto& n2 = x->Node2();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		Debug_Null_Pointer(n2);

		auto length = factor * face.CharLength();
		auto criterion = length * length;
		auto dist_sq = 
			MetricMap()->CalcSquareDistanceFromTriangle
			(
				coord, n0->Coord(),
				n1->Coord(), n2->Coord()
			);
		if (dist_sq < criterion)
		{
			return Standard_False;
		}
	}
	// this protects the algorithm to produce the nodes which are very close to the current [2/27/2023 Payvand]
	const auto& current = *Current();
	const auto& n0 = current.Node0();
	const auto& n1 = current.Node1();
	const auto& n2 = current.Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	const auto dist_sq = 
		MetricMap()->CalcSquareDistanceFromTriangle
		(
			coord, n0->Coord(),
			n1->Coord(), n2->Coord()
		);
	const auto length = factor * current.CharLength();
	const auto criterion = length * length;
	if (dist_sq < criterion)
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsNewEdgeValid
(
	const Pnt3d& theP0,
	const Pnt3d& theP1,
	const std::vector<std::shared_ptr<Aft3d_Edge>>& theFronts
) const
{
	const auto factor = MinDistFactor();
	Debug_If_Condition(factor <= 0.0);

	for (const auto& x : theFronts)
	{
		Debug_Null_Pointer(x);
		const auto& edge = *x;
		const auto& n0 = edge.Node0();
		const auto& n1 = edge.Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto length = factor * edge.CharLength();
		auto criterion = length * length;
		auto dist_sq = 
			MetricMap()->CalcSquareDistanceEdgeFromEdge
			(
				theP0, theP1,
				n0->Coord(), n1->Coord());
		if (dist_sq < criterion)
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsSameLevelSupplied()
{
	if (FrontHandler.IsCurrentEmpty())
	{
		return Standard_False;
	}
	auto faces = FrontHandler.RetrieveCurrentLevel();
	FrontHandler.InsertToFronts(faces);
	FrontHandler.ClearCurrent();
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsNextLevelSupplied()
{
	if (FrontHandler.IsNextEmtpy())
	{
		return Standard_False;
	}
	auto faces = FrontHandler.RetrieveNexLevel();
	for (const auto& x : faces)
	{
		Debug_Null_Pointer(x);
		if (x->IsCavity())
		{
			x->SetAsNonCavity();
		}
	}
	FrontHandler.InsertToFronts(faces);
	FrontHandler.ClearNext();
	FrontHandler.SetMaxLevel(Mesh.MaxNodeIdx());
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsCavityRemoverSupplied()
{
	if (Cavities.IsUncertaintyEmpty())
	{
		return Standard_False;
	}
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		auto faces = Cavities.RetrieveUncertainties();
		for (const auto& x : faces)
		{
			Debug_Null_Pointer(x);
			if (x->IsCavity())
			{
				x->SetAsNonCavity();
			}
		}
		FrontHandler.InsertToFronts(faces);
		Cavities.ClearUncertainty();
		return Standard_True;
	}
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::repair)
	{
		auto faces = Cavities.RetrieveUncertainties();
		for (const auto& x : faces)
		{
			Debug_Null_Pointer(x);
			if (x->IsCavity())
			{
				Cavities.InsertToCertainty(x);
			}
		}
		Cavities.ClearUncertainty();
		return Standard_False;
	}
	FatalErrorIn(FunctionSIG)
		<< "unspecified type of cycle has been detected." << endl
		<< abort(FatalError);
	return Standard_True;
}

void tnbLib::legLib::Aft3d_VolumeCore::RetrieveEarlyNodes
(
	std::vector<std::shared_ptr<Aft3d_Node>>& theNodes
) const
{
	Debug_Null_Pointer(MetricMap());
	const auto& metricMap = *MetricMap();
	Debug_Null_Pointer(Current());
	const auto& current = *Current();

	auto reg = 
		metricMap.CalcSearchingRegion
		(
			CycleInfo.SearchRadius(), CycleInfo.Coord(), 
			current);
	std::vector<std::shared_ptr<Aft3d_Node>> nodes;
	Engine()->GeometrySearch(reg, nodes);
	theNodes = 
		NodesInRadius
		(
			CycleInfo.SearchRadius(),
			CycleInfo.Coord(), metricMap, nodes);
}

void tnbLib::legLib::Aft3d_VolumeCore::RetrieveLocalFrontNodes
(
	std::vector<std::shared_ptr<Aft3d_Node>>& theLocals,
	std::vector<std::shared_ptr<Aft3d_Node>>& theSearching
)
{
	Debug_Null_Pointer(MetricMap());
	Debug_Null_Pointer(CycleInfo.Current());

	const auto& sizeMap = *MetricMap();
	const auto& current = *CycleInfo.Current();
	const auto& coord = CycleInfo.Coord();

	std::vector<std::shared_ptr<Aft3d_Node>> locals;

	Entity3d_Box box;
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		box = sizeMap.CalcSearchingRegion
		(
			CycleInfo.LocalFrontRadius(), 
			coord, 
			current
		);
	}
	else
	{
		box = sizeMap.CalcSearchingRegion
		(
			CycleInfo.LocalFrontRadius(),
			current
		);
	}

	Engine()->GeometrySearch(box, locals);

	Debug_If_Condition_Message(CycleInfo.SquareSearchRadius() <= 0, "Invalid searching radius");
	const auto squareSearchingRadius = CycleInfo.SquareSearchRadius();

	Debug_If_Condition_Message(CycleInfo.SquareLocalFrontRadius() <= 0, "Invalid local radius");
	const auto squareLocalRadius = CycleInfo.SquareLocalFrontRadius();

	std::vector<Pnt3d> pts;
	pts.reserve(locals.size());
	for (const auto& node : locals)
	{
		if(current.Node0() IS_EQUAL node) continue;
		if(current.Node1() IS_EQUAL node) continue;
		if(current.Node2() IS_EQUAL node) continue;

		auto r2 = sizeMap.CalcSquareDistance(coord, node->Coord());
		if (r2 <= squareSearchingRadius)
		{
			theSearching.push_back(node);
		}
		if (r2 <= squareLocalRadius)
		{
			theLocals.push_back(node);
		}
	}
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		CycleInfo.SetCandidateSize((Standard_Integer)pts.size());
		if (pts.size())
		{
			auto b = Geo_BoxTools::GetBox(pts, 0);
			auto bptr = std::make_shared<Entity3d_Box>(std::move(b));
			CycleInfo.SetRegion(std::move(bptr));
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::RetrieveLocalFrontEntities
(
	const std::vector<std::shared_ptr<Aft3d_Node>>& theNodes,
	std::vector<std::shared_ptr<Aft3d_Facet>>& theEntities
) const
{
	std::set<std::shared_ptr<Aft3d_Facet>, decltype(cmp_facet)> compact(cmp_facet);
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		auto entities = x->FrontFacets();
		for (const auto& ent : entities)
		{
			Debug_Null_Pointer(ent.second.lock());
			compact.insert(ent.second.lock());  // ignoring duplicate entities [6/3/2023 Payvand]
		}
	}
	std::copy(compact.begin(), compact.end(), std::back_inserter(theEntities));
}

void tnbLib::legLib::Aft3d_VolumeCore::RetrieveEffectiveFronts
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFronts, 
	std::vector<std::shared_ptr<Aft3d_Facet>>& theEffectives
) const
{
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::repair)
	{
		std::copy(theFronts.begin(), theFronts.end(), std::back_inserter(theEffectives));
		return;
	}
	Debug_Null_Pointer(theMetricMap_);
	const auto& metricMap = *theMetricMap_;
	Debug_Null_Pointer(metricMap.Domain());
	const auto& domain = *metricMap.Domain();

	if (NOT domain.IsInside(CycleInfo.Coord()))
	{
		std::copy(theFronts.begin(), theFronts.end(), std::back_inserter(theEffectives));
		return;
	}

	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();
	Debug_Null_Pointer(CycleInfo.Region());
	const auto& bx0 = *CycleInfo.Region();

	const auto& coord = CycleInfo.Coord();
	const auto rad = metricMap.CalcDistance(coord, current.CalcCentre());
	const auto bx1 = metricMap.CalcEffectiveFront(rad, coord, current);

	Entity3d_Box box;
	if (CycleInfo.CandidateSize())
	{
		box = Entity3d_Box::Union(bx0, bx1);
	}
	else
	{
		box = bx1;
	}
	auto Pmin = box.P0();
	auto Pmax = box.P1();
	Debug_Null_Pointer(current.Node0());
	Debug_Null_Pointer(current.Node1());
	Debug_Null_Pointer(current.Node2());
	Update_Pmin_Pmax(current.Node0()->Coord(), Pmin, Pmax);
	Update_Pmin_Pmax(current.Node1()->Coord(), Pmin, Pmax);
	Update_Pmin_Pmax(current.Node2()->Coord(), Pmin, Pmax);

	Update_Pmin_Pmax(box.P0(), Pmin, Pmax);
	Update_Pmin_Pmax(box.P1(), Pmin, Pmax);

	theEffectives.reserve(theFronts.size());
	for (const auto& f : theFronts)
	{
		Debug_Null_Pointer(f);
		if (IsIntersect(*f, Pmin, Pmax))
		{
			theEffectives.push_back(f);
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::SortNodes
(
	std::vector<std::shared_ptr<Aft3d_Node>>& theNodes
) const
{
	if (theNodes.size() < 2)
	{
		return;
	}
	Debug_Null_Pointer(theMetricMap_);
	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	auto centre = current.CalcCentre();

	std::vector<std::pair<std::shared_ptr<Aft3d_Node>, Standard_Real>> quality;
	quality.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		auto paired = std::make_pair(x, theMetricMap_->CalcDistance(centre, x->Coord()));
		quality.push_back(std::move(paired));
	}
	std::sort
	(
		quality.begin(), 
		quality.end(), 
		[](
			const std::pair<std::shared_ptr<Aft3d_Node>, Standard_Real>& p0,
			const std::pair<std::shared_ptr<Aft3d_Node>, Standard_Real>& p1
			) {return p0.second < p1.second; }
	);
	theNodes.clear();
	theNodes.reserve(quality.size());
	for (const auto& x : quality)
	{
		theNodes.push_back(x.first);
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::AddOptimumNodeTo
(
	std::vector<std::shared_ptr<Aft3d_Node>>& theNodes
)
{
	auto node = std::make_shared<Aft3d_InteriorNode>
		(Counter.NbNodes() + 1, CycleInfo.Coord());
	CycleInfo.SetTempNode(node);
	theNodes.push_back(std::move(node));
	CycleInfo.AppendedNode() = Standard_True;
}

void tnbLib::legLib::Aft3d_VolumeCore::CalcLocalFrontRadius()
{
	Debug_Null_Pointer(Current());
	const auto& current = *Current();
	const auto& coord = CycleInfo.Coord();

	Debug_Null_Pointer(MetricMap());
	const auto& metricMap = *MetricMap();
	if (CycleMode() IS_EQUAL cycleMode::generation)
	{
		auto maxLength = (Standard_Real)0.;
		for (const auto& x : current.GetNodes())
		{
			auto len = metricMap.CalcDistance(coord, x->Coord());
			if (len > maxLength)
			{
				maxLength = len;
			}
		}
		maxLength = std::max(maxLength, CycleInfo.Size() / SIZE_TO_HIGHT_ELEMENT_COEFF) * 1.12;
		CycleInfo.SetMaxElmLength(maxLength);

		auto srch_rad = current.SearchRadius();
		auto ratio = std::max(maxLength / current.CharLength(), 1.0);
		CycleInfo.SetLocRadius(ratio * srch_rad);
	}
	else
	{
		auto maxLength = CycleInfo.Size() / SIZE_TO_HIGHT_ELEMENT_COEFF;
		CycleInfo.SetMaxElmLength(maxLength);

		auto srch_rad = current.SearchRadius();
		CycleInfo.SetLocRadius(std::max(srch_rad, std::min(metricMap.DimSize(), maxLength)));
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::ModifyLocalFront
(
	const Standard_Real theFactor
)
{
	if (theFactor < 1.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid factor has been detected." << endl
			<< abort(FatalError);
	}
	if (theEngine_->IsGeometryEmpty())
	{
		return; // no front has been found [6/2/2023 Payvand]
	}
	Debug_Null_Pointer(MetricMap());
	const auto& sizeMap = *MetricMap();

	std::vector<std::shared_ptr<Aft3d_Node>> nodes;
	Engine()->RetrieveFromGeometryTo(nodes);

	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		auto& node = *x;
		const auto& pt = node.Coord();

		const auto& fronts = node.FrontEdges();
		Debug_If_Condition(NOT fronts.size());

		//- Retrieve max_length attached to the current node
		Standard_Real maxLength = (Standard_Real)0.;
		for (const auto& w_entity : fronts)
		{
			Debug_Null_Pointer(w_entity.second.lock());
			auto entity = w_entity.second.lock();

			if (entity->CharLength() > maxLength)
				maxLength = entity->CharLength();
		}

		maxLength *= theFactor;
		Debug_If_Condition_Message
		(
			maxLength <= (Standard_Real)0.,
			" Invalid MaxLength Value"
		);

		//- save the max_length
		node.FrontSpecsRef().SetRadius
		(
			MAX(node.FrontSpecs().Radius(), maxLength)
		);

		std::vector<std::shared_ptr<Aft3d_Node>> locals;
		Engine()->GeometrySearch
		(
			sizeMap.CalcSearchingRegion(maxLength, node.Coord()),
			locals
		);

		std::vector<std::shared_ptr<Aft3d_Node>> inners = 
			NodesInRadius(maxLength, node.Coord(), *MetricMap(), locals);

		for (const auto& innerNode : inners)
		{
			innerNode->FrontSpecsRef().SetRadius
			(std::max(innerNode->FrontSpecs().Radius(), maxLength));
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::RemoveEntitiesFromGeometry()
{
	Debug_Null_Pointer(CycleInfo.Element());
	auto& element = *CycleInfo.Element();

	if (NOT element.Node0()->NbFrontEdges())
	{
		theEngine_->RemoveFromGeometry(element.Node0());
	}
	if (NOT element.Node1()->NbFrontEdges())
	{
		theEngine_->RemoveFromGeometry(element.Node1());
	}
	if (NOT element.Node2()->NbFrontEdges())
	{
		theEngine_->RemoveFromGeometry(element.Node2());
	}
	if (NOT element.Node3()->NbFrontEdges())
	{
		theEngine_->RemoveFromGeometry(element.Node3());
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::RemoveCurrentFromFront()
{
	Debug_Null_Pointer(CycleInfo.Current());
	deAttachFromFronts(CycleInfo.Current());
}

void tnbLib::legLib::Aft3d_VolumeCore::CalcElementSize()
{
	Debug_Null_Pointer(CycleInfo.Current());
	Debug_Null_Pointer(theMetricMap_);
	CycleInfo.SetElementSize
	(
		theMetricMap_->ElementSize(*CycleInfo.Current()) 
		* SIZE_TO_HIGHT_ELEMENT_COEFF);
}

void tnbLib::legLib::Aft3d_VolumeCore::CalcOptimumCoord()
{
	Debug_Null_Pointer(CycleInfo.Current());
	Debug_Null_Pointer(theMetricMap_);
	Debug_Null_Pointer(CoordCalculator());

	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		auto pt = CoordCalculator()->CalcCoord(CycleInfo.Size(), CycleInfo.Current(), this);
		CycleInfo.SetCoord(std::move(pt));
	}
	else
	{
		auto pt = CycleInfo.Current()->CalcCentre();
		CycleInfo.SetCoord(std::move(pt));
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::SetSearchingDepth()
{
	Debug_Null_Pointer(theMetricMap_);
	const auto& metricMap = *theMetricMap_;

	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		CycleInfo.SetSearchRadius
		(
			0.95 * std::max
			(
				metricMap.CalcDistance(CycleInfo.Coord(), current.CalcCentre()),
				CycleInfo.Size()
			)
			);
	}
	else
	{
		CycleInfo.SetSearchRadius(CycleInfo.LocalFrontRadius());
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::SetPairedEdges()
{
	CycleInfo.SetPairedEdge3(nullptr);
	CycleInfo.SetPairedEdge4(nullptr);
	CycleInfo.SetPairedEdge5(nullptr);

	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	Debug_Null_Pointer(current.Node0());
	Debug_Null_Pointer(current.Node1());
	Debug_Null_Pointer(current.Node2());

	const auto v0 = current.Node0()->Index();
	const auto v1 = current.Node1()->Index();
	const auto v2 = current.Node2()->Index();

	Debug_Null_Pointer(CycleInfo.ValidNode());
	const auto& valid = *CycleInfo.ValidNode();

	const auto vn = valid.Index();
	for (const auto& x : valid.FrontEdges())
	{
		auto edge_ptr = x.second.lock();
		Debug_Null_Pointer(edge_ptr);

		const auto& edge = *edge_ptr;

		const auto e0 = edge.Node0()->Index();
		const auto e1 = edge.Node1()->Index();

		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v0, vn))
		{
			CycleInfo.SetPairedEdge3(edge_ptr);
		}
		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v1, vn))
		{
			CycleInfo.SetPairedEdge4(edge_ptr);
		}
		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v2, vn))
		{
			CycleInfo.SetPairedEdge5(edge_ptr);
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::SetPairedFacets()
{
	CycleInfo.SetPairedFacet0(nullptr);
	CycleInfo.SetPairedFacet1(nullptr);
	CycleInfo.SetPairedFacet2(nullptr);

	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	const auto v0 = current.Node0()->Index();
	const auto v1 = current.Node1()->Index();
	const auto v2 = current.Node2()->Index();

	Debug_Null_Pointer(current.Edge0());
	Debug_Null_Pointer(current.Edge1());
	Debug_Null_Pointer(current.Edge2());

	const auto& facets0 = current.Edge0()->Fronts();
	const auto& facets1 = current.Edge1()->Fronts();
	const auto& facets2 = current.Edge2()->Fronts();

	const auto& valid = *CycleInfo.ValidNode();
	const auto vn = valid.Index();

	for (const auto& x : facets0)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v1, v2, vn, q0, q1, q2))
		{
			CycleInfo.SetPairedFacet0(facetPtr);
			break;
		}
	}
	for (const auto& x : facets1)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v2, v0, vn, q0, q1, q2))
		{
			CycleInfo.SetPairedFacet1(facetPtr);
			break;
		}
	}
	for (const auto& x : facets2)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v0, v1, vn, q0, q1, q2))
		{
			CycleInfo.SetPairedFacet2(facetPtr);
			break;
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::SetPairs()
{
	SetPairedEdges();
	SetPairedFacets();
}

void tnbLib::legLib::Aft3d_VolumeCore::CalcGeometries
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	Debug_Null_Pointer(theMetricMap_);

	auto& edge = *theEdge;
	const auto& p0 = edge.Node0()->Coord();
	const auto& p1 = edge.Node1()->Coord();

	edge.SetCharLength(theMetricMap_->CalcDistance(p0, p1));
}

void tnbLib::legLib::Aft3d_VolumeCore::CalcGeometries
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);

	auto& facet = *theFacet;
	const auto& e0 = facet.Edge0();
	const auto& e1 = facet.Edge1();
	const auto& e2 = facet.Edge2();
	Debug_Null_Pointer(e0);
	Debug_Null_Pointer(e1);
	Debug_Null_Pointer(e2);

	facet.SetCharLength
	(
		std::max
		(
			e0->CharLength(), 
			std::max(e1->CharLength(), e2->CharLength())
		)
	);
}

void tnbLib::legLib::Aft3d_VolumeCore::UpdateEdges()
{
	Debug_Null_Pointer(theMetricMap_);
	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	if (CycleInfo.PairedEdge3())
	{
		CycleInfo.SetCreatedEdge3(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(CycleInfo.PairedEdge3());
	}
	else
	{
		Counter.NbEdges()++;

		std::array<std::shared_ptr<Aft3d_Node>, 2> paired = { current.Node0(), CycleInfo.ValidNode() };
		auto edge = std::make_shared<Aft3d_InteriorEdge>(Counter.NbEdges(), std::move(paired));
		Debug_Null_Pointer(edge);

		CycleInfo.SetCreatedEdge3(edge);

		CalcGeometries(edge);

		Debug_If_Condition(CycleInfo.ValidNode() == current.Node0());

		AttachToFrontNodes(CycleInfo.CreatedEdge3());
		AttachToMeshNodes(CycleInfo.CreatedEdge3());
	}

	if (CycleInfo.PairedEdge4())
	{
		CycleInfo.SetCreatedEdge4(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(CycleInfo.PairedEdge4());
	}
	else
	{
		Counter.NbEdges()++;

		std::array<std::shared_ptr<Aft3d_Node>, 2> paired = { current.Node1() ,CycleInfo.ValidNode() };
		auto edge = std::make_shared<Aft3d_InteriorEdge>(Counter.NbEdges(), std::move(paired));
		Debug_Null_Pointer(edge);

		CycleInfo.SetCreatedEdge4(edge);

		CalcGeometries(edge);

		Debug_If_Condition(CycleInfo.ValidNode() == current.Node1());

		AttachToFrontNodes(CycleInfo.CreatedEdge4());
		AttachToMeshNodes(CycleInfo.CreatedEdge4());
	}

	if (CycleInfo.PairedEdge5())
	{
		CycleInfo.SetCreatedEdge5(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(CycleInfo.PairedEdge5());
	}
	else
	{
		Counter.NbEdges()++;

		std::array<std::shared_ptr<Aft3d_Node>, 2> paired = { current.Node2() , CycleInfo.ValidNode() };
		auto edge = std::make_shared<Aft3d_InteriorEdge>(Counter.NbEdges(), std::move(paired));
		Debug_Null_Pointer(edge);

		CycleInfo.SetCreatedEdge5(edge);

		CalcGeometries(edge);

		Debug_If_Condition(CycleInfo.ValidNode() == current.Node2());

		AttachToFrontNodes(CycleInfo.CreatedEdge5());
		AttachToMeshNodes(CycleInfo.CreatedEdge5());
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::UpdateFacets()
{
	Debug_Null_Pointer(CycleInfo.Current());
	const auto& current = *CycleInfo.Current();

	const auto e0 = current.Edge0();
	const auto e1 = current.Edge1();
	const auto e2 = current.Edge2();

	std::shared_ptr<Aft3d_Edge> e3, e4, e5;

	if (CycleInfo.CreatedEdge3()) e3 = CycleInfo.CreatedEdge3();
	else e3 = CycleInfo.PairedEdge3();

	if (CycleInfo.CreatedEdge4()) e4 = CycleInfo.CreatedEdge4();
	else e4 = CycleInfo.PairedEdge4();

	if (CycleInfo.CreatedEdge5()) e5 = CycleInfo.CreatedEdge5();
	else e5 = CycleInfo.PairedEdge5();

	Debug_Null_Pointer(e0);
	Debug_Null_Pointer(e1);
	Debug_Null_Pointer(e2);
	Debug_Null_Pointer(e3);
	Debug_Null_Pointer(e4);

	{
		auto facet = CycleInfo.PairedFacet0();
		if (facet)
		{
			CycleInfo.SetCreatedFacet0(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsCavity())
			{
				facet->SetAsNonCavity();
			}
		}
		else
		{
			Counter.NbFacets()++;

			std::array<std::shared_ptr<Aft3d_Node>, 3> nodes 
				= { current.Node1(), current.Node2(), CycleInfo.ValidNode() };
			auto newFacet =
				std::make_shared<Aft3d_InteriorFacet>
				(
					Counter.NbFacets(),
					std::move(nodes)
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e5);
			newFacet->SetEdge1(e4);
			newFacet->SetEdge2(e0);

			CycleInfo.SetCreatedFacet0(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(newFacet);
		}
	}

	{
		auto facet = CycleInfo.PairedFacet1();
		if (facet)
		{
			CycleInfo.SetCreatedFacet1(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsCavity())
			{
				facet->SetAsNonCavity();
			}
		}
		else
		{
			Counter.NbFacets()++;

			std::array<std::shared_ptr<Aft3d_Node>, 3> nodes
				= { current.Node2(), current.Node0(), CycleInfo.ValidNode() };
			auto newFacet =
				std::make_shared<Aft3d_InteriorFacet>
				(
					Counter.NbFacets(),
					std::move(nodes)
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e3);
			newFacet->SetEdge1(e5);
			newFacet->SetEdge2(e1);

			CycleInfo.SetCreatedFacet1(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(newFacet);
		}
	}

	{
		auto facet = CycleInfo.PairedFacet2();
		if (facet)
		{
			CycleInfo.SetCreatedFacet2(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsCavity())
			{
				facet->SetAsNonCavity();
			}
		}
		else
		{
			Counter.NbFacets()++;

			std::array<std::shared_ptr<Aft3d_Node>, 3> nodes 
				= { current.Node0(), current.Node1(), CycleInfo.ValidNode() };
			auto newFacet =
				std::make_shared<Aft3d_InteriorFacet>
				(
					Counter.NbFacets(),
					std::move(nodes)
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e4);
			newFacet->SetEdge1(e3);
			newFacet->SetEdge2(e2);

			CycleInfo.SetCreatedFacet2(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(newFacet);
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::UpdatePairs()
{
	UpdateEdges();
	UpdateFacets();
}

void tnbLib::legLib::Aft3d_VolumeCore::UpdateElement()
{
	const auto& element = CycleInfo.Element();
	Debug_Null_Pointer(element);

	AttachToMesh(element);

	/*Attaching the element to the facets*/

	const auto& current = CycleInfo.Current();
	Debug_Null_Pointer(current);

	// update right/ left side element pointer of the faces
	// update the adjacent elements
	current->SetUpperElement(element);
	element->SetNeighbor3(current->LowerElement().lock());

	auto rightElement = current->LowerElement().lock();
	if (rightElement)
	{
		rightElement->Neighbor(rightElement->OppositeVertexIndex(current)) = element;
	}

	if (CycleInfo.CreatedFacet0())
	{
		CycleInfo.CreatedFacet0()->SetLowerElement(element);
		element->SetNeighbor0(nullptr);
	}
	else
	{
		auto facet = CycleInfo.PairedFacet0();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->LowerElement().lock();
		element->SetNeighbor0(neighbor);

		if (facet->UpperElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetUpperElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}

	if (CycleInfo.CreatedFacet1())
	{
		CycleInfo.CreatedFacet1()->SetLowerElement(element);
		element->SetNeighbor1(nullptr);
	}
	else
	{
		auto facet = CycleInfo.PairedFacet1();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->LowerElement().lock();
		element->SetNeighbor1(neighbor);

		if (facet->UpperElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetUpperElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}

	if (CycleInfo.CreatedFacet2())
	{
		CycleInfo.CreatedFacet2()->SetLowerElement(element);
		element->SetNeighbor2(nullptr);
	}
	else
	{
		auto facet = CycleInfo.PairedFacet2();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->LowerElement().lock();
		element->SetNeighbor2(neighbor);

		if (facet->UpperElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetUpperElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}
}

void tnbLib::legLib::Aft3d_VolumeCore::CreateElement()
{
	Counter.NbElements()++;

	Debug_Null_Pointer(CycleInfo.Current());
	Debug_Null_Pointer(CycleInfo.ValidNode());
	const auto& current = *CycleInfo.Current();

	std::array<std::shared_ptr<Aft3d_Node>, 4> nodes
		= { current.Node0(), current.Node1(), current.Node2(), CycleInfo.ValidNode() };
	auto element_p =
		std::make_shared<Aft3d_Element>(Counter.NbElements(), std::move(nodes));
	Debug_Null_Pointer(element_p);

	auto& element = *element_p;

	element.SetEdge0(current.Edge0());
	element.SetEdge1(current.Edge1());
	element.SetEdge2(current.Edge2());


	if (CycleInfo.CreatedFacet0())
	{
		element.SetFacet0(CycleInfo.CreatedFacet0());
	}
	else
	{
		element.SetFacet0(CycleInfo.PairedFacet0());
	}

	if (CycleInfo.CreatedFacet1())
	{
		element.SetFacet1(CycleInfo.CreatedFacet1());
	}
	else
	{
		element.SetFacet1(CycleInfo.PairedFacet1());
	}

	if (CycleInfo.CreatedFacet2())
	{
		element.SetFacet2(CycleInfo.CreatedFacet2());
	}
	else
	{
		element.SetFacet2(CycleInfo.PairedFacet2());
	}

	if (CycleInfo.CreatedEdge3())
	{
		element.SetEdge3(CycleInfo.CreatedEdge3());
	}
	else
	{
		element.SetEdge3(CycleInfo.PairedEdge3());
	}

	if (CycleInfo.CreatedEdge4())
	{
		element.SetEdge4(CycleInfo.CreatedEdge4());
	}
	else
	{
		element.SetEdge4(CycleInfo.PairedEdge4());
	}

	if (CycleInfo.CreatedEdge5())
	{
		element.SetEdge5(CycleInfo.CreatedEdge5());
	}
	else
	{
		element.SetEdge5(CycleInfo.PairedEdge5());
	}

	element.SetFacet3(CycleInfo.Current());

	CycleInfo.SetElement(std::move(element_p));
}

void tnbLib::legLib::Aft3d_VolumeCore::RegisterElement()
{
	Debug_Null_Pointer(CycleInfo.Current());
	Mesh.Insert(CycleInfo.Element());
}

std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Node>> 
tnbLib::legLib::Aft3d_VolumeCore::NodesInRadius
(
	const Standard_Real theRadius,
	const Pnt3d& theCoord, 
	const Aft3d_GeoPrcsr& theMetricMap,
	const std::vector<std::shared_ptr<Aft3d_Node>>& theNodes
)
{
	Debug_If_Condition_Message(theRadius <= 0.0, "invalid search radius");
	const Standard_Real sq_rad = theRadius * theRadius;
	std::vector<std::shared_ptr<Aft3d_Node>> nodes;
	nodes.reserve(theNodes.size());
	Debug_Null_Pointer(MetricMap());
	for (const auto& x : theNodes)
	{
		if (theMetricMap.CalcSquareDistance(theCoord, x->Coord()) <= sq_rad)
		{
			nodes.push_back(x);
		}
	}
	return std::move(nodes);
}

void tnbLib::legLib::Aft3d_VolumeCore::Update_Pmin_Pmax
(
	const Pnt3d& P,
	Pnt3d& Pmin,
	Pnt3d& Pmax
)
{
	if (P.X() > Pmax.X()) Pmax.X() = P.X();
	if (P.X() < Pmin.X()) Pmin.X() = P.X();

	if (P.Y() > Pmax.Y()) Pmax.Y() = P.Y();
	if (P.Y() < Pmin.Y()) Pmin.Y() = P.Y();

	if (P.Z() > Pmax.Z()) Pmax.Z() = P.Z();
	if (P.Z() < Pmin.Z()) Pmin.Z() = P.Z();
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsIntersect
(
	const Pnt3d& Q0,
	const Pnt3d& Q1,
	const Pnt3d& Pmin,
	const Pnt3d& Pmax
)
{
	auto xmax = MAX(Q0.X(), Q1.X());
	if (xmax < Pmin.X()) return Standard_False;

	auto xmin = MIN(Q0.X(), Q1.X());
	if (xmin > Pmax.X()) return Standard_False;

	auto ymax = MAX(Q0.Y(), Q1.Y());
	if (ymax < Pmin.Y()) return Standard_False;

	auto ymin = MIN(Q0.Y(), Q1.Y());
	if (ymin > Pmax.Y()) return Standard_False;

	auto zmax = MAX(Q0.Z(), Q1.Z());
	if (zmax < Pmin.Z()) return Standard_False;

	auto zmin = MIN(Q0.Z(), Q1.Z());
	if (zmin > Pmax.Z()) return Standard_False;

	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_VolumeCore::IsIntersect
(
	const Aft3d_Facet& theFacet, 
	const Pnt3d& theP0, 
	const Pnt3d& theP1
)
{
	const auto& p0 = Aft3d_Tools::GetCoord0(theFacet);
	const auto& p1 = Aft3d_Tools::GetCoord1(theFacet);
	const auto& p2 = Aft3d_Tools::GetCoord2(theFacet);

	auto b = Geo_BoxTools::GetBox(p0, p1, p2);
	return IsIntersect(b->P0(), b->P1(), theP0, theP1);
}
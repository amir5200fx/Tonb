#include <Aft3d_Volume.hxx>

#include <Aft3d_GeoPrcsr.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <Aft3d_InteriorNode.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::legLib::Aft3d_VolumeCore::SIZE_TO_HIGHT_ELEMENT_COEFF = 0.866025404;

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

		auto length = factor * face.CharLenght();
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
	// this protects the algorithm to produce the nodes very close to the current [2/27/2023 Payvand]
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
	const auto length = factor * current.CharLenght();
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
			x->SetAsNotCavity();
		}
	}
	FrontHandler.InsertToFronts(faces);
	FrontHandler.ClearNext();
	FrontHandler.SetMaxLevel(Mesh.NbNodes());
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
				x->SetAsNotCavity();
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
	Debug_Null_Pointer(Current());
	Debug_Null_Pointer(Engine());

	const auto& metricMap = *MetricMap();
	const auto& current = *Current();

	auto reg = CalcSearchingRegion();

	Engine()->GeometrySearch(reg, theLocals);

	Debug_If_Condition_Message
	(
		CycleInfo.SquareSearchRadius() <= 0.0,
		"Invalid searching radius"
	);
	const auto square_srch_rad = CycleInfo.SquareSearchRadius();

	const auto& coord = CycleInfo.Coord();

	std::vector<Pnt3d> pnts;
	pnts.reserve(theLocals.size());
	for (const auto& node : theLocals)
	{
		Standard_Boolean cond = Standard_False;
		forThose(Index, 0, Aft3d_Facet::nbNodes - 1)
		{
			if (node IS_EQUAL current.Node(Index))
			{
				cond = Standard_True;
				break;
			}
		}
		if (cond)
		{
			continue;
		}

		auto rad_2 = 
			metricMap.CalcSquareDistance(coord, node->Coord());
		if (rad_2 <= square_srch_rad)
		{
			theSearching.push_back(node);
			if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
			{
				pnts.push_back(node->Coord());
			}
		}
	}
	if (CycleInfo.CycleMode() IS_EQUAL cycleMode::generation)
	{
		CycleInfo.SetCandidateSize((Standard_Integer)pnts.size());
		if (pnts.size())
		{
			auto box_ref = Geo_BoxTools::GetBox(pnts, 0);
			auto box = std::make_shared<Entity3d_Box>(std::move(box_ref));
			CycleInfo.SetRegion(std::move(box));
		}
	}
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

void tnbLib::legLib::Aft3d_VolumeCore::AddOptimumNodeTo
(
	std::vector<std::shared_ptr<Aft3d_Node>>& theNodes
)
{
	auto node = std::make_shared<Aft3d_InteriorNode>
		(CycleInfo.NodeCounter() + 1, CycleInfo.Coord());
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
		auto ratio = std::max(maxLength / current.CharLenght(), 1.0);
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

void tnbLib::legLib::Aft3d_VolumeCore::CalcElementSize()
{
	Debug_Null_Pointer(CycleInfo.Current());
	Debug_Null_Pointer(theMetricMap_);
	CycleInfo.SetElementSize
	(
		theMetricMap_->ElementSize(*CycleInfo.Current()) 
		* SIZE_TO_HIGHT_ELEMENT_COEFF);
}

void tnbLib::legLib::Aft3d_VolumeCore::SetDepthSearching()
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
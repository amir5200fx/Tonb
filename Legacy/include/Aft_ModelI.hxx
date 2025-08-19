#pragma once
template<class ModelType, class SizeFun, class MetricFun>
inline tnbLib::Entity_Box<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::Point>
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveBoundingBox
(
	const std::vector<std::shared_ptr<nodeType>>& theNodes
)
{
	std::vector<Point> pts;
	pts.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		pts.push_back(x->Coord());
	}
	auto box = Entity_Box<Point>::BoundingBoxOf(pts);
	return std::move(box);
}

template<class ModelType, class SizeFun, class MetricFun>
inline Standard_Integer tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::Meshing()
{
	if (base::IsPriorityEmpty())
	{
		FatalErrorIn("void AutLib::Mesh_Plane::Perform()")
			<< "Empty priority list" << endl
			<< abort(FatalError);
	}

	frontData::SetLevelNumber(0);
	frontData::SetLevelMaxIndex(base::NodeCounter());

	base::AlgCondition() = Aft_AlgCondition::Generation;

	//const auto startTime = (Standard_Real)getCPUTime();

	/*fileName outPutName("meshingOutPuts.txt");
	OFstream outPuts(outPutName);*/

	while (NOT base::IsPriorityEmpty())
	{
		MeshingOneLevel(/*outPuts*/);

		if (base::IsSameLevelFueled())
		{
			base::AlgCondition() = Aft_AlgCondition::Generation;
			continue;
		}

		if (base::IsCavityRemoverFueled())
		{
			base::AlgCondition() = Aft_AlgCondition::Repair;
			continue;
		}

		frontData::SetLevelNumber(frontData::LevelNumber() + 1);

		if (frontData::LevelNumber() >= ALLOWED_MAX_LEVEL_GENERATION)
		{
			return 1;
		}

		if (base::IsNextLevelFueled())
		{
			base::AlgCondition() = Aft_AlgCondition::Generation;
		}
	}

	return 0;
}

#ifndef AFT_MODEL_DEBUG
template<class ModelType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::MeshingOneLevel()
{
	base::ModifyLocalFront(DEFAULT_LOCALFRONT_FACTOR);

	while (base::GetFrontEntity())
	{
		std::vector<std::shared_ptr<nodeType>>
			CandidateNodes,
			LocalNodes;

		std::vector<std::shared_ptr<frontType>>
			Effectives,
			Local;

		if (NOT base::IsBelongToFront())
			continue;

		// Remove the Current from front
		base::RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		base::CalcElementSize();

		// Calculate optimum coordinate of new point
		base::CalcOptimumCoord();

		base::CalcLocalFrontRadius();

		// Set depth of searching radius
		base::SetDepthSearching();

		base::RetrieveLocalFrontNodes(LocalNodes, CandidateNodes);

		base::RetrieveLocalFrontEntities(LocalNodes, Local);

		base::RetrieveEffectiveFronts(Local, Effectives);

		base::SortNodes(CandidateNodes);

		if (base::IsNewPointCandidate(Effectives))
		{
			base::AddOptimumNodeTo(CandidateNodes);
		}

		FindValidNode(CandidateNodes, Effectives);

		Update();
	}
}
#endif // AFT_MODEL_DEBUG


template<class ModelType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::Update()
{
	if (base::ValidNode())
	{
		base::UpdateFront();

		InsertNewFrontsToLevels();
	}
	else
	{
		base::RejectCurrent(base::CurrentFront());
	}
}

template<class ModelType, class SizeFun, class MetricFun>
inline Standard_Boolean tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::IsBoundaryLoaded() const
{
	return theBoundaryEntity_.size();
}

template<class ModelType, class SizeFun, class MetricFun>
inline Standard_Boolean tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::IsBoundaryMapLoaded() const
{
	return Standard_Boolean(theBoundaryMap_);
}

template<class ModelType, class SizeFun, class MetricFun>
inline Standard_Boolean tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::IsLoaded() const
{
	if (NOT base::IsMetricMapLoaded()) return Standard_False;
	if (NOT IsBoundaryLoaded()) return Standard_False;
	if (NOT IsBoundaryMapLoaded()) return Standard_False;
	return Standard_True;
}

template<class ModelType, class SizeFun, class MetricFun>
inline const std::vector<std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::frontType>>& 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::GetBoundaryEntities() const
{
	return theBoundaryEntity_;
}

template<class ModelType, class SizeFun, class MetricFun>
inline const std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::staticMesh>& 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::GetTriangulation() const
{
	return theTriangulation_;
}

template<class ModelType, class SizeFun, class MetricFun>
inline const std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::metricPrcsr>& 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::GetBoundaryMap() const
{
	return theBoundaryMap_;
}

template<class ModelType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::Perform()
{
	base::SetPriorityFunction(&frontType::Length);
	base::SetMinDistFactor(DEFAULT_MIN_DISTANCE_FACTOR);

	base::SetGeometryCoordFunc(&nodeType::GetCoord);

	ActiveFront(GetBoundaryEntities());

	Import(GetBoundaryEntities(), GetBoundaryMap());

	Meshing();
}

template<class ModelType, class SizeFun, class MetricFun>
inline void tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::CreateStaticMesh()
{
	std::vector<std::shared_ptr<elementType>> elements;
	elements.reserve(this->NbElements());
	for (const auto& x : this->RetrieveElements())
	{
		elements.push_back(x.second);
	}

	CompactNumbering(elements);

	theTriangulation_ =
		std::make_shared<staticMesh>
		(
			RetrieveGeometryFrom
			(
				RetrieveNodesFrom(elements)
			), RetrieveGeometryFrom(elements, *cache::NodesIndices));
}

template<class ModelType, class SizeFun, class MetricFun>
inline std::vector<std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::nodeType>> 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveNodesFrom
(
	const std::vector<std::shared_ptr<frontType>>& theFronts
)
{
	Adt_AvlTree<std::shared_ptr<nodeType>> compact;
	compact.SetComparableFunction(&nodeType::IsLess);

	for (const auto& x : theFronts)
	{
		Debug_Null_Pointer(x);
		const auto& ent = *x;

		for (int i = 0; i < ent.NbNodes(); i++)
		{
			compact.InsertIgnoreDup(ent.Node(i));
		}
	}
	std::vector<std::shared_ptr<nodeType>> nodes;
	compact.RetrieveTo(nodes);

	return std::move(nodes);
}

template<class ModelType, class SizeFun, class MetricFun>
inline std::vector<std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::nodeType>>
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveNodesFrom
(
	const std::vector<std::shared_ptr<elementType>>& theElements
)
{
	Adt_AvlTree<std::shared_ptr<nodeType>> compact;
	compact.SetComparableFunction(&nodeType::IsLess);

	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		const auto& ent = *x;

		for (int i = 0; i < ent.NbNodes(); i++)
		{
			compact.InsertIgnoreDup(ent.Node(i));
		}
	}
	std::vector<std::shared_ptr<nodeType>> nodes;
	compact.RetrieveTo(nodes);

	return std::move(nodes);
}

template<class ModelType, class SizeFun, class MetricFun>
inline std::vector<std::shared_ptr<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::frontType>> 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveEdgesFrom
(
	const std::vector<std::shared_ptr<elementType>>& theElements
)
{
	Adt_AvlTree<std::shared_ptr<frontType>> compact;
	compact.SetComparableFunction(&frontType::IsLess);

	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		const auto& element = *x;

		for (int i = 0; i < element.NbEdges(); i++)
		{
			compact.InsertIgnoreDup(element.Edge(i));
		}
	}
	std::vector<std::shared_ptr<frontType>> edges;
	compact.RetrieveTo(edges);

	return std::move(edges);
}

template<class ModelType, class SizeFun, class MetricFun>
inline std::vector<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::Point> 
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveGeometryFrom
(
	const std::vector<std::shared_ptr<nodeType>>& theNodes
)
{
	std::vector<Point> pts;
	pts.reserve(theNodes.size());

	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		pts.push_back(x->Coord());
	}
	return std::move(pts);
}

template<class ModelType, class SizeFun, class MetricFun>
inline std::vector<typename tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::elementType::connectType>
tnbLib::Aft_Model<ModelType, SizeFun, MetricFun>::RetrieveGeometryFrom
(
	const std::vector<std::shared_ptr<elementType>>& theElements,
	std::map<unsigned, unsigned>& theNodesIndices
)
{
	std::vector<typename elementType::connectType> triangles;
	triangles.reserve(theElements.size());

	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		auto t = x->RetrieveConnectivity();
		triangles.push_back(std::move(t));
	}
	return std::move(triangles);
}
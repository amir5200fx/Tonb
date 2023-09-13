#include <VoyageMesh_CoreBase.hxx>

#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_RefNode.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

template<>
Standard_Boolean 
tnbLib::VoyageMesh_CoreBase::IsSameLevelFueled()
{
	if (NOT NbUnCertaintyCavities())
	{
		return Standard_False;
	}

	const auto& entities = RetrieveUnCertaintyCavities();
	SetSizeToPriority((Standard_Integer)entities.size());
	Standard_Boolean isCavity = Standard_False;
	//std::cout << "size = " << entities.size() << std::endl;
	//PAUSE;
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x.second);
		if (x.second->IsOnCavity())
		{
			x.second->RemoveEntityAsCavity();
		}
		if (x.second->IsReference())
		{
			isCavity = Standard_True;
			//std::cout << "YES" << std::endl;
			InsertToPriority(x.second);
		}	
	}
	ClearUnCertaintyCavities();
	return isCavity;
}

template<>
Standard_Boolean 
tnbLib::VoyageMesh_CoreBase::IsCavityRemoverFueled()
{
	if (NOT frontData::NbUnCertaintyCavities())
	{
		return Standard_False;
	}

	if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition::Generation)
	{
		const auto& entities = frontData::RetrieveUnCertaintyCavities();
		frontData::SetSizeToPriority((Standard_Integer)entities.size());
		for (const auto& x : entities)
		{
			Debug_Null_Pointer(x.second);
			if (x.second->IsOnCavity())
			{
				x.second->RemoveEntityAsCavity();
			}
			frontData::InsertToPriority(x.second);
		}
		frontData::ClearUnCertaintyCavities();
		return Standard_True;
	}

	if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition::Repair)
	{
		const auto& entities = frontData::RetrieveUnCertaintyCavities();
		for (const auto& x : entities)
		{
			Debug_Null_Pointer(x.second);
			frontData::InsertToCertaintyCavities(x.second->Index(), x.second);
		}

		frontData::ClearUnCertaintyCavities();
		return Standard_False;
	}

	FatalErrorIn(FunctionSIG)
		<< "Something goes wrong!"
		<< abort(FatalError);

	return Standard_True;
}

template<>
void tnbLib::VoyageMesh_CoreBase::AddOptimumNodeTo
(
	std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes
)
{
	auto node = std::make_shared<VoyageMesh_Node>(NodeCounter() + 1, Coord());
	SetTempoNode(node);
	Debug_Null_Pointer(CurrentFront());
	const auto current_lev = CurrentFront()->Region();
	Debug_Null_Pointer(node);
	node->SetRegion(current_lev);
	std::vector<std::shared_ptr<VoyageMesh_Node>> nodes;
	for (const auto& x : theNodes)
	{
		if (x->Region() NOT_EQUAL current_lev)
		{
			if (NOT x->IsReference())
			{
				nodes.push_back(x);
			}		
		}
	}
	nodes.push_back(std::move(node));
	for (const auto& x : theNodes)
	{
		if (x->Region() IS_EQUAL current_lev)
		{
			if (NOT x->IsReference())
			{
				nodes.push_back(x);
			}
		}
	}
	theNodes.clear();
	theNodes = nodes;
}

template<>
template<>
void tnbLib::VoyageMesh_CoreBase::RetrieveLocalFrontEntities<void>
(
	const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes,
	std::vector<std::shared_ptr<VoyageMesh_Edge>>& theEdges
) const
{
	static auto cmp = [](const std::shared_ptr<VoyageMesh_EdgeBase>& e0, const std::shared_ptr<VoyageMesh_EdgeBase>& e1)
	{
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		return e0->Index() < e1->Index();
	};
	std::set<std::shared_ptr<VoyageMesh_Edge>, decltype(cmp)> compact(cmp);
	for (const auto& x : theNodes)
	{
		Debug_Null_Pointer(x);
		auto edges = x->RetrieveFrontEdges();
		for (const auto& e : edges)
		{
			auto edge = e.second.lock();
			Debug_Null_Pointer(edge);
			auto insert = compact.insert(std::move(edge));
			if (NOT insert.second)
			{
				// do nothing [8/22/2023 aamir]
			}
		}
	}
	std::copy(compact.begin(), compact.end(), std::back_inserter(theEdges));
}

template<>
void tnbLib::VoyageMesh_CoreBase::CalcElementSize()
{
	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& n0 = this->CurrentFront()->Node0();
	const auto& n1 = this->CurrentFront()->Node1();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(theMetricMap_);
	/*std::cout<<"min size : " << std::min(theMetricMap_->CalcElementSize(n0->Coord()) *
		SIZE_TO_HIGHT_ELEMENT_COEFF, theMetricMap_->CalcElementSize(n1->Coord()) *
		SIZE_TO_HIGHT_ELEMENT_COEFF) << std::endl;*/
	frontInfo::SetElementSize
	(
		std::min(theMetricMap_->CalcElementSize(n0->Coord()) *
			SIZE_TO_HIGHT_ELEMENT_COEFF, theMetricMap_->CalcElementSize(n1->Coord()) *
			SIZE_TO_HIGHT_ELEMENT_COEFF)
	);
}

template<>
void tnbLib::VoyageMesh_CoreBase::CalcLocalFrontRadius()
{
	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	const auto& coord = frontInfo::Coord();

	Debug_Null_Pointer(theMetricMap_);
	const auto& sizeMap = *theMetricMap_;

	if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition::Generation)
	{
		auto maxLenght = (Standard_Real)0.;
		forThose(Iter, 0, frontType::nbNodes - 1)
		{
			Standard_Real length =
				sizeMap.CalcDistance(coord, current.Node(Iter)->Coord());

			if (length > maxLenght) maxLenght = length;
		}

		maxLenght = MAX(maxLenght, frontInfo::ElementSize() / SIZE_TO_HIGHT_ELEMENT_COEFF) * 1.12;
		frontInfo::SetMaxElmLength(maxLenght);

		auto sr = current.SearchRadius();
		auto ratio = MAX(maxLenght / current.CharLength(), 1.0);

		frontInfo::SetLocFrontRadius(ratio * sr);
	}
	else
	{
		auto maxLenght = (Standard_Real)0.;
		forThose(Iter, 0, frontType::nbNodes - 1)
		{
			Standard_Real length =
				sizeMap.CalcDistance(coord, current.Node(Iter)->Coord());

			if (length > maxLenght) maxLenght = length;
		}

		maxLenght = MAX(maxLenght, frontInfo::ElementSize() / SIZE_TO_HIGHT_ELEMENT_COEFF) * 1.12;
		frontInfo::SetMaxElmLength(maxLenght);

		auto sr = current.SearchRadius();
		auto ratio = MAX(maxLenght / current.CharLength(), 1.0);

		frontInfo::SetLocFrontRadius(ratio * sr * 5);
	}
}
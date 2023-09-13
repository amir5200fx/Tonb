#include <VoyageMesh_CoreBase.hxx>

#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

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
			nodes.push_back(x);
		}
	}
	nodes.push_back(std::move(node));
	for (const auto& x : theNodes)
	{
		if (x->Region() IS_EQUAL current_lev)
		{
			nodes.push_back(x);
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
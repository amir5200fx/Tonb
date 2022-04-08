#pragma once
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Next
(
	const std::shared_ptr<nodeType>& theNode,
	std::shared_ptr<edgeType>& theEdge
)
{
	if (theNode->Type() NOT_EQUAL Knit_ChainNode_Type::regular)
	{
		if (NOT theNode->NbEdges())
		{
			base::RemoveItem(theNode);
		}
		return nullptr;
	}

	auto edges = theNode->RetrieveEdges();
	
	std::shared_ptr<edgeType> edge;
	std::shared_ptr<nodeType> next;

	if (edges.size() > 1)
	{
		Standard_Integer cond = 1;
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x.lock());
			edge = std::dynamic_pointer_cast<edgeType>(x.lock());
			Debug_Null_Pointer(edge);

			if (edge->Node0() IS_EQUAL theNode)
			{
				cond = 0;
				break;
			}
		}

		if (cond)
		{
			FatalErrorIn(FunctionSIG)
				<< "no start node has been found!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		edge = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
		Debug_Null_Pointer(edge);
	}

	theNode->RemoveFromEdges(edge->Index());
	base::RemoveItem(edge);

	next = std::dynamic_pointer_cast<nodeType>(edge->Node1());
	Debug_Null_Pointer(next);

	if (next IS_EQUAL theNode)
	{
		FatalErrorIn(FunctionSIG)
			<< "the chain is not oriented!" << endl
			<< abort(FatalError);
	}

	if (edges.size() IS_EQUAL 1)
	{
		base::RemoveItem(theNode);
	}
	else
	{
		auto edges = theNode->RetrieveEdges();
		Standard_Integer cond = 1;
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x.lock());
			auto seg = std::dynamic_pointer_cast<edgeType>(x.lock());
			Debug_Null_Pointer(seg);

			if (seg->Node0() IS_EQUAL theNode)
			{
				cond = 0;
				break;
			}

			if (cond)
			{
				theNode->TypeRef() = Knit_ChainNode_Type::end;
			}
			else
			{
				theNode->TypeRef() = Knit_ChainNode_Type::start;
			}
		}
	}

	next->RemoveFromEdges(edge->Index());
	theEdge = edge;
	return std::move(next);
}

template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::FindStart
(
	const Knit_ChainNode_Type t
) const
{
	auto nodes = base::Nodes();
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x.second);
		if (x.second->Type() IS_EQUAL t)
		{
			x.second->TypeRef() = Knit_ChainNode_Type::start;
			return x.second;
		}
	}
	return nullptr;
}

template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::entityType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::GetEntity
(
	const std::shared_ptr<nodeType>& theStart
)
{
	theStart->TypeRef() = Knit_ChainNode_Type::regular;
	auto poly = std::make_shared<entityType>();
	Debug_Null_Pointer(poly);

	auto& ents = poly->EntitiesRef();
	std::shared_ptr<edgeType> edge;
	auto next = Next(theStart, edge);

	while (next)
	{
		ents.push_back(edge);
		next = Next(next, edge);
	}
	return std::move(poly);
}

template<class ChainTraits>
inline std::vector<std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType>>
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::GetNodes() const
{
	std::map<Standard_Integer, std::shared_ptr<nodeType>> compact;
	for (const auto& x : theRegister_)
	{
		Debug_Null_Pointer(x.second);
		const auto& l = x.second->Entities();
		for (const auto& p : l)
		{
			{
				auto n = std::dynamic_pointer_cast<nodeType>(p->Node0());
				Debug_Null_Pointer(n);
				auto paired = std::make_pair(n->Index(), std::move(n));
				auto insert = compact.insert(std::move(paired));
				if (NOT insert.second)
				{
					// do nothing [4/1/2022 Amir]
				}
			}

			{
				auto n = std::dynamic_pointer_cast<nodeType>(p->Node1());
				Debug_Null_Pointer(n);
				auto paired = std::make_pair(n->Index(), std::move(n));
				auto insert = compact.insert(std::move(paired));
				if (NOT insert.second)
				{
					// do nothing [4/1/2022 Amir]
				}
			}
		}
	}
	std::vector<std::shared_ptr<nodeType>> nodes;
	nodes.reserve(compact.size());
	for (auto& x : compact)
	{
		auto& n = x.second;
		nodes.push_back(std::move(n));
	}
	return std::move(nodes);
}

template<class ChainTraits>
inline std::vector<std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::edgeType>>
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::GetEdges() const
{
	std::vector<std::shared_ptr<edgeType>> edges;
	edges.reserve(theRegister_.size());
	for (const auto& x : theRegister_)
	{
		Debug_Null_Pointer(x.second);
		const auto& l = x.second->Entities();
		for (const auto& p : l)
		{
			edges.push_back(p);
		}
	}
	return std::move(edges);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::SetTypes()
{
	const auto& nodes = base::Nodes();
	for (const auto& n : nodes)
	{
		const auto& x = n.second;
		Debug_Null_Pointer(x);

		if (x->NbEdges() IS_EQUAL 1)
		{
			auto edges = x->RetrieveEdges();
			auto edge = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
			Debug_Null_Pointer(edge);

			if (edge->Node0() IS_EQUAL x)
			{
				// start node [4/1/2022 Amir]
				x->TypeRef() = Knit_ChainNode_Type::start;
			}
			else
			{
				x->TypeRef() = Knit_ChainNode_Type::end;
			}
		}
		else if (x->NbEdges() IS_EQUAL 2)
		{
			auto edges = x->RetrieveEdges();

			Standard_Integer cond = 1;
			for (const auto& wie : edges)
			{
				Debug_Null_Pointer(wie.lock());
				auto ie = std::dynamic_pointer_cast<edgeType>(wie.lock());
				Debug_Null_Pointer(ie);
				if (ie->Node0() IS_EQUAL x)
				{
					cond = 0;
					break;
				}
			}

			if (cond)
			{
				x->TypeRef() = Knit_ChainNode_Type::end;
			}
			else
			{
				x->TypeRef() = Knit_ChainNode_Type::start;
			}
		}
		else
		{
			// regular node [4/1/2022 Amir]
			x->TypeRef() = Knit_ChainNode_Type::regular;
		}
	}
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::CompleteTopology()
{
	for (const auto& x : theRegister_)
	{
		Debug_Null_Pointer(x.second);		

		const auto& l = x.second->Entities();
		for (const auto& e : l)
		{
			Debug_Null_Pointer(e);

			e->Node0()->InsertToEdges(e->Index(), e);
			e->Node1()->InsertToEdges(e->Index(), e);
		}
	}
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::UpdateNodeTypes
(
	const std::shared_ptr<nodeType>& theNode
) const
{
	if (theNode->NbEdges() IS_EQUAL 2)
	{
		theNode->TypeRef() = Knit_ChainNode_Type::regular;
	}
	else if (theNode->NbEdges() IS_EQUAL 1)
	{
		auto edges = theNode->RetrieveEdges();

		auto e = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
		Debug_Null_Pointer(e);
		if (e->Node0() IS_EQUAL theNode)
		{
			theNode->TypeRef() = Knit_ChainNode_Type::start;
		}
		else
		{
			theNode->TypeRef() = Knit_ChainNode_Type::end;
		}
	}
}

template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::entityType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::deAttachEntity
(
	const Standard_Integer theIndex
)
{
	auto item = Global_Tools::Find(theRegister_, theIndex);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(item->First());
	auto fn = std::dynamic_pointer_cast<nodeType>(item->First()->Node0());
	Debug_Null_Pointer(fn);

	Debug_Null_Pointer(item->End());
	auto en = std::dynamic_pointer_cast<nodeType>(item->End()->Node1());
	Debug_Null_Pointer(en);

	fn->RemoveFromEdges(item->First()->Index());
	en->RemoveFromEdges(item->End()->Index());

	auto cfn = std::make_shared<nodeType>(++theMaxIndex_, fn->Coord());
	Debug_Null_Pointer(cfn);

	auto cen = std::make_shared<nodeType>(++theMaxIndex_, en->Coord());
	Debug_Null_Pointer(cen);

	UpdateNodeTypes(fn);
	UpdateNodeTypes(en);

	cfn->TypeRef() = Knit_ChainNode_Type::start;
	cen->TypeRef() = Knit_ChainNode_Type::end;

	item->First()->SetNode0(cfn);
	item->End()->SetNode1(cen);

	return std::move(item);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Perform()
{
	Standard_Integer k = 0;

	// create regular chains [4/2/2022 Amir]
	auto start = FindStart(Knit_ChainNode_Type::start);
	while (start)
	{
		auto ent = std::make_pair(++k, GetEntity(start));
		ent.second->IsRingRef() = Standard_False;

		theRegister_.insert(std::move(ent));

		start = FindStart(Knit_ChainNode_Type::start);
	}

	// create ring chains [4/2/2022 Amir]
	if (base::NbEdges())
	{
		start = FindStart(Knit_ChainNode_Type::regular);
		while (start)
		{
			auto ent = std::make_pair(++k, GetEntity(start));
			ent.second->IsRingRef() = Standard_True;

			theRegister_.insert(std::move(ent));

			start = FindStart(Knit_ChainNode_Type::regular);
		}
	}

	if (base::NbNodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "the node tree is not empty!" << endl
			<< abort(FatalError);
	}

	if (base::NbEdges())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge tree is not empty!" << endl
			<< abort(FatalError);
	}

	CompleteTopology();
	Change_IsDone() = Standard_True;
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Import
(
	const Entity_StaticData<Point, connectivity::dual>& theChain
)
{
	const auto& points = theChain.Points();
	const auto& indices = theChain.Connectivity();

	std::vector<std::shared_ptr<nodeType>> nodes;
	nodes.reserve(points.size());

	{ // import the nodes [4/2/2022 Amir]
		Standard_Integer k = 0;
		for (const auto& x : points)
		{
			auto n = std::make_shared<nodeType>(++k, x);
			Debug_Null_Pointer(n);
			nodes.push_back(n);
			base::Insert(std::move(n));

			theMaxIndex_++;
		}
	}

	{
		Standard_Integer k = 0;
		for (const auto& x : indices)
		{
			auto v0 = x.Value(0);
			auto v1 = x.Value(1);

			auto e = std::make_shared<edgeType>(++k, nodes[Index_Of(v0)], nodes[Index_Of(v1)]);
			Debug_Null_Pointer(e);

			base::Insert(e);

			nodes[Index_Of(v0)]->InsertToEdges(e->Index(), e);
			nodes[Index_Of(v1)]->InsertToEdges(e->Index(), e);
		}
	}
	SetTypes();
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::reLink()
{
	const auto nodes = GetNodes();
	const auto edges = GetEdges();

	for (const auto& x : nodes)
	{
		base::Insert(x);
	}

	for (const auto& x : edges)
	{
		base::Insert(x);
	}

	SetTypes();

	theRegister_.clear();

	Perform();
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::reReisterEdges()
{
	for (const auto& x : theRegister_)
	{
		Debug_Null_Pointer(x.second);
		const auto& l = x.second->Entities();
		for (const auto& e : l)
		{
			base::Insert(e);
		}
	}
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::DestroyEntity
(
	const Standard_Integer theIndex
)
{
	auto iter = theRegister_.find(theIndex);
	if (iter IS_EQUAL theRegister_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the map" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(iter->second);
	auto& l = iter->second->EntitiesRef();
	for (const auto& x : l)
	{
		Debug_Null_Pointer(x);

		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		n0->RemoveFromEdges(x->Index());
		n1->RemoveFromEdges(x->Index());
	}
	l.clear();
	theRegister_.erase(iter);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Descrete()
{
	std::list<Standard_Integer> ents;
	for (const auto& x : theRegister_)
	{
		ents.push_back(x.first);
	}
	for (const auto x : ents)
	{
		deAttachEntity(x);
	}
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::RemoveFromRegistry
(
	const Standard_Integer theIndex
)
{
	auto iter = theRegister_.find(theIndex);
	if (iter IS_EQUAL theRegister_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree" << endl
			<< abort(FatalError);
	}
	theRegister_.erase(iter);
}
#pragma once
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class ChainTraits>
inline Standard_Integer 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::NbEnds() const
{
	return (Standard_Integer)theEnds_.size();
}

template<class ChainTraits>
inline std::vector<std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType>> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::RetrieveEnds() const
{
	std::vector<std::shared_ptr<nodeType>> nodes;
	for (const auto& x : theEnds_)
	{
		nodes.push_back(x.second);
	}
	return std::move(nodes);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::ImportToEnds
(
	const std::shared_ptr<nodeType>& theNode
)
{
	Global_Tools::Insert(theNode->Index(), theNode, theEnds_);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::RemoveFromEnds
(
	const std::shared_ptr<nodeType>& theNode
)
{
	auto iter = theEnds_.find(theNode->Index());
	if (iter IS_EQUAL theEnds_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the map!" << endl
			<< abort(FatalError);
	}
	theEnds_.erase(iter);
}

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::RegisterEnds()
{
	for (const auto& x : base::Nodes())
	{
		Debug_Null_Pointer(x.second);
		auto node = std::dynamic_pointer_cast<nodeType>(x.second);
		Debug_Null_Pointer(node);
		if (node->Type() IS_EQUAL Knit_ChainNode_Type::start)
		{
			node->TypeRef() = Knit_ChainNode_Type::end;
			ImportToEnds(node);
		}
	}
}

template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::RetrieveStart(const Standard_Boolean ringPoint)
{
	if (NOT NbEnds())
	{
		return nullptr;
	}
	auto ends = RetrieveEnds();
	std::shared_ptr<nodeType> node;
	for (const auto& x : ends)
	{
		/*if (ringPoint AND IsRing(x))
		{
			node = x;
			break;
		}
		else */if (/*NOT ringPoint AND */IsStart(x))
		{
			node = x;
			break;
		}
		else
		{
			RemoveFromEnds(x);
		}
	}
	if (NOT node)
	{
		return nullptr;
	}
	Debug_Null_Pointer(node);
	//RemoveFromEnds(node);

	node->TypeRef() = Knit_ChainNode_Type::start;
	return std::move(node);
}

#ifndef _DEBUG
template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType>
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Next
(
	const std::shared_ptr<nodeType>& theNode,
	std::shared_ptr<edgeType>& theEdge
)
{
	if (theNode->Type() IS_EQUAL Knit_ChainNode_Type::end)
	{
		if (NOT theNode->NbEdges())
		{
			base::RemoveItem(theNode);
		}
		return nullptr;
	}

	if (theNode->Type() IS_EQUAL Knit_ChainNode_Type::start)
	{
		theNode->TypeRef() = Knit_ChainNode_Type::end;
	}

	auto edges = theNode->RetrieveEdges();

	std::shared_ptr<edgeType> edge;
	std::shared_ptr<nodeType> next;

	/*if (edges.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to decide the path!" << endl
			<< " - the node is not regular" << endl
			<< abort(FatalError);
	}*/
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

	try
	{
		theNode->RemoveFromEdges(edge->Index());
	}
	catch (const error& err)
	{
		FatalErrorIn(FunctionSIG)
			<< err.message() << endl
			<< abort(FatalError);
	}
	base::RemoveItem(edge);

	if (edge->Node0() IS_EQUAL theNode)
	{
		next = std::dynamic_pointer_cast<nodeType>(edge->Node1());
	}
	else if (edge->Node1() IS_EQUAL theNode)
	{
		next = std::dynamic_pointer_cast<nodeType>(edge->Node0());
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to track the path!" << endl
			<< abort(FatalError);
	}

	const auto isRing = next IS_EQUAL theNode;

	Debug_Null_Pointer(next);
	try
	{
		if (isRing)
		{
			// the edge is ring [5/21/2022 Amir]
		}
		else
		{
			next->RemoveFromEdges(edge->Index());
		}
	}
	catch (const error& err)
	{
		FatalErrorIn(FunctionSIG)
			<< err.message() << endl
			<< abort(FatalError);
	}

	/*if (next IS_EQUAL theNode)
	{
		FatalErrorIn(FunctionSIG)
			<< "the chain is not oriented!" << endl
			<< abort(FatalError);
	}*/

	if (edges.size() IS_EQUAL 1 AND NOT isRing)
	{
		base::RemoveItem(theNode);
	}
	/*else
	{
		auto edges0 = theNode->RetrieveEdges();
		Standard_Integer cond = 1;
		for (const auto& x : edges0)
		{
			Debug_Null_Pointer(x.lock());
			auto seg = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(x.lock());
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
	}*/

	theEdge = edge;
	return std::move(next);
}
#endif // !_DEBUG

template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::nodeType> 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::FindStart
(
	const Knit_ChainNode_Type t
) const
{
	const auto& nodes = base::Nodes();
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
	//theStart->TypeRef() = Knit_ChainNode_Type::regular;
	auto poly = std::make_shared<entityType>();
	Debug_Null_Pointer(poly);

	auto& ents = poly->EntitiesRef();
	std::shared_ptr<edgeType> edge;
	auto next = Next(theStart, edge);
	if (NOT next)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid chain has been detected!" << endl
			<< abort(FatalError);
	}
	auto last = next;
	while (next)
	{
		ents.push_back(edge);
		next = Next(next, edge);
		if (next)
		{
			last = next;
		}
	}
	//SetType(theStart);
	//SetType(last);
	return std::move(poly);
}

#ifndef _DEBUG
template<class ChainTraits>
inline std::shared_ptr<typename tnbLib::Geo_TopoChainAnalysis<ChainTraits>::entityType>
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::GetRing
(
	const std::shared_ptr<nodeType>& theNode
)
{
	auto sn = std::make_shared<nodeType>(++theMaxIndex_, theNode->Coord());
	Debug_Null_Pointer(sn);
	sn->TypeRef() = Knit_ChainNode_Type::start;

	auto fn = std::make_shared<nodeType>(++theMaxIndex_, theNode->Coord());
	Debug_Null_Pointer(fn);
	fn->TypeRef() = Knit_ChainNode_Type::end;

	auto edges = theNode->RetrieveEdges();
	if (edges.size() IS_EQUAL 1)
	{
		auto edge = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
		Debug_Null_Pointer(edge);

		if (edge->Node0() NOT_EQUAL edge->Node1())
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not regular!" << endl
				<< abort(FatalError);
		}

		edge->SetNode0(sn);
		edge->SetNode1(fn);

		sn->InsertToEdges(edge->Index(), edge);
		fn->InsertToEdges(edge->Index(), edge);
	}
	else
	{
		if (edges.size() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not regular!" << endl
				<< abort(FatalError);
		}

		{
			auto edge = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
			Debug_Null_Pointer(edge);

			if (edge->Node0() IS_EQUAL theNode)
			{
				edge->SetNode0(sn);
			}
			else if (edge->Node1() IS_EQUAL theNode)
			{
				edge->SetNode1(sn);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data has been detected!" << endl
					<< abort(FatalError);
			}
			sn->InsertToEdges(edge->Index(), edge);
		}

		{
			auto edge = std::dynamic_pointer_cast<edgeType>(edges.at(1).lock());
			Debug_Null_Pointer(edge);

			if (edge->Node0() IS_EQUAL theNode)
			{
				edge->SetNode0(fn);
			}
			else if (edge->Node1() IS_EQUAL theNode)
			{
				edge->SetNode1(fn);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data has been detected!" << endl
					<< abort(FatalError);
			}
			fn->InsertToEdges(edge->Index(), edge);
		}
	}

	theNode->ClearEdges();

	base::RemoveItem(theNode);

	base::Insert(sn);
	base::Insert(fn);

	auto ent = GetEntity(sn);
	return std::move(ent);
}
#endif // !_DEBUG

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
			if (p->Node0() IS_EQUAL p->Node1())
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
			else
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
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::SetNodesToNone()
{
	for (const auto& x : base::Nodes())
	{
		Debug_Null_Pointer(x.second);
		auto node = std::dynamic_pointer_cast<nodeType>(x.second);
		Debug_Null_Pointer(node);
		node->TypeRef() = Knit_ChainNode_Type::none;
	}
}

#ifndef _DEBUG
template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::SetType
(
	const std::shared_ptr<nodeType>& x
) const
{
	if (x->Type() IS_EQUAL Knit_ChainNode_Type::none)
	{
		if (x->NbEdges() IS_EQUAL 1)
		{
			auto edges = x->RetrieveEdges();
			auto edge = std::dynamic_pointer_cast<edgeType>(edges.at(0).lock());
			Debug_Null_Pointer(edge);

			if (edge->Node0() IS_EQUAL edge->Node1())
			{
				// the edge is a ring [5/22/2022 Amir]
				x->TypeRef() = Knit_ChainNode_Type::regular;
			}
			else
			{
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
		}
		else if (x->NbEdges() > 2)
		{
			//x->TypeRef() = Knit_ChainNode_Type::end;
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
	else
	{
		/*if (x->Type() IS_EQUAL Knit_ChainNode_Type::end)
		{
			x->TypeRef() = Knit_ChainNode_Type::start;
		}*/
	}
}
#endif // !_DEBUG

template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::SetTypes() const
{
	const auto& nodes = base::Nodes();
	for (const auto& n : nodes)
	{
		const auto& x = n.second;
		Debug_Null_Pointer(x);
		SetType(x);
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

			if (e->Node0() IS_EQUAL e->Node1())
			{
				// the segment is a ring [5/22/2022 Amir]
				e->Node0()->InsertToEdges(e->Index(), e);
			}
			else
			{
				e->Node0()->InsertToEdges(e->Index(), e);
				e->Node1()->InsertToEdges(e->Index(), e);
			}	
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
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::BreakRing()
{
	if (NOT base::NbNodes())
	{
		return;
	}

	// Get a sample point [5/22/2022 Amir]
	for (const auto& x : base::Nodes())
	{
		Debug_Null_Pointer(x.second);
		if (IsStart(x.second))
		{
			const auto& node = x.second;
			node->TypeRef() = Knit_ChainNode_Type::start;

			ImportToEnds(node);
			return;
		}
	}
	if (base::NbNodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "Unable to find a start point!" << endl
			<< abort(FatalError);
	}
}

template<class ChainTraits>
inline Standard_Boolean 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::IsStart
(
	const std::shared_ptr<nodeType>& x
)
{
	auto edges = x->RetrieveEdges();
	if (edges.empty())
	{
		return Standard_False;
	}

	Standard_Integer cond = 0;
	for (const auto& wie : edges)
	{
		Debug_Null_Pointer(wie.lock());
		auto ie = std::dynamic_pointer_cast<edgeType>(wie.lock());
		Debug_Null_Pointer(ie);
		if (ie->Node0() IS_EQUAL x)
		{
			cond = 1;
			break;
		}
	}
	if (cond)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

template<class ChainTraits>
inline Standard_Boolean 
tnbLib::Geo_TopoChainAnalysis<ChainTraits>::IsRing
(
	const std::shared_ptr<nodeType>& x
)
{
	auto edges = x->RetrieveEdges();
	if (edges.empty())
	{
		/*FatalErrorIn(FunctionSIG)
			<< "the edge list is empty." << endl
			<< abort(FatalError);*/
		return Standard_False;
	}

	for (const auto& wie : edges)
	{
		Debug_Null_Pointer(wie.lock());
		auto ie = std::dynamic_pointer_cast<edgeType>(wie.lock());
		Debug_Null_Pointer(ie);
		if (ie->Node0() IS_EQUAL ie->Node1())
		{
			return Standard_True;
		}
	}
	return Standard_False;
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

#ifndef _DEBUG
template<class ChainTraits>
inline void tnbLib::Geo_TopoChainAnalysis<ChainTraits>::Perform()
{
	RegisterEnds();

	Standard_Integer k = 0;
	// create regular chains [4/2/2022 Amir]
	//auto start = FindStart(Knit_ChainNode_Type::start);
	auto start = RetrieveStart();
	while (start)
	{
		if (start->Type() NOT_EQUAL Knit_ChainNode_Type::start)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type for a start point" << endl
				<< abort(FatalError);
		}
		auto ent = std::make_pair(++k, GetEntity(start));
		ent.second->IsRingRef() = Standard_False;

		theRegister_.insert(std::move(ent));

		//start = FindStart(Knit_ChainNode_Type::start);
		start = RetrieveStart();
	}

	// create ring chains [4/2/2022 Amir]
	if (base::NbEdges())
	{
		BreakRing();
		//start = FindStart(Knit_ChainNode_Type::regular);	
		start = RetrieveStart(Standard_True);
		while (start)
		{
			//start->TypeRef() = Knit_ChainNode_Type::start;

			auto ent = std::make_pair(++k, GetRing(start));
			ent.second->IsRingRef() = Standard_True;

			theRegister_.insert(std::move(ent));

			//start = FindStart(Knit_ChainNode_Type::regular);
			BreakRing();

			start = RetrieveStart(Standard_True);
		}
	}
	for (const auto& x : theRegister_)
	{
		const auto& n0 = x.second->First()->Node0();
		const auto& n1 = x.second->End()->Node1();

		if (n0->Coord().Distance(n1->Coord()) <= gp::Resolution())
		{
			x.second->IsRingRef() = Standard_True;
		}
	}

	if (base::NbNodes())
	{
		FatalErrorIn(FunctionSIG)
			<< "the node tree is not empty!" << endl
			<< " - nb nodes: " << base::NbNodes() << endl
			<< abort(FatalError);
	}

	if (base::NbEdges())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge tree is not empty!" << endl
			<< " - nb edges: " << base::NbEdges() << endl
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
			n->TypeRef() = Knit_ChainNode_Type::none;
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

			if (nodes[Index_Of(v0)] IS_EQUAL nodes[Index_Of(v1)])
			{
				nodes[Index_Of(v0)]->InsertToEdges(e->Index(), e);
			}
			else
			{
				nodes[Index_Of(v0)]->InsertToEdges(e->Index(), e);
				nodes[Index_Of(v1)]->InsertToEdges(e->Index(), e);
			}
		}
	}
	SetTypes();
}
#endif // !_DEBUG

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

	/*for (const auto& x : edges)
	{
		auto e = std::dynamic_pointer_cast<edgeType>(x);
		Debug_Null_Pointer(e);
		Debug_Null_Pointer(e->Node0());
		Debug_Null_Pointer(e->Node1());
		e->Node0()->InsertToEdges(e->Index(), e);
		e->Node1()->InsertToEdges(e->Index(), e);
	}*/

	SetNodesToNone();

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

		if (n0 IS_EQUAL n1)
		{
			n0->RemoveFromEdges(x->Index());
		}
		else
		{
			n0->RemoveFromEdges(x->Index());
			n1->RemoveFromEdges(x->Index());
		}	
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
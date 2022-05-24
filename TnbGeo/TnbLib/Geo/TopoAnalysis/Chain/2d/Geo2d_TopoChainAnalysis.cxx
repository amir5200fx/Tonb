#include <Geo2d_TopoChainAnalysis.hxx>
#ifdef _DEBUG
#include <Geo2d_RingGraphEdge.hxx>
template<>
std::shared_ptr<tnbLib::Geo2d_TopoChainAnalysis_Node> 
tnbLib::Geo2d_TopoChainAnalysis::Next
(
	const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>& theNode, 
	std::shared_ptr<Geo2d_SegmentGraphEdge>& theEdge
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

	std::shared_ptr<Geo2d_SegmentGraphEdge> edge;
	std::shared_ptr<Geo2d_TopoChainAnalysis_Node> next;

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
			edge = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(x.lock());
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
		edge = std::dynamic_pointer_cast<Geo2d_SegmentGraphEdge>(edges.at(0).lock());
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
		next = std::dynamic_pointer_cast<Geo2d_TopoChainAnalysis_Node>(edge->Node1());
	}
	else if (edge->Node1() IS_EQUAL theNode)
	{
		next = std::dynamic_pointer_cast<Geo2d_TopoChainAnalysis_Node>(edge->Node0());
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

template<>
std::shared_ptr<typename tnbLib::Geo2d_TopoChainAnalysis::entityType> 
tnbLib::Geo2d_TopoChainAnalysis::GetRing
(
	const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>& theNode
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

template<>
void tnbLib::Geo2d_TopoChainAnalysis::SetType
(
	const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>& x
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

template<>
void tnbLib::Geo2d_TopoChainAnalysis::Perform()
{
	RegisterEnds();
	std::cout << "nb of nodes: " << base::NbNodes() << std::endl;
	std::cout << "nb of edges: " << base::NbEdges() << std::endl;
	std::cout << std::endl;
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
	std::cout << "nb of nodes: " << base::NbNodes() << std::endl;
	std::cout << "nb of edges: " << base::NbEdges() << std::endl;
	std::cout << std::endl;
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



template<>
void tnbLib::Geo2d_TopoChainAnalysis::Import(const Entity2d_Chain& theChain)
{
	const auto& points = theChain.Points();
	const auto& indices = theChain.Connectivity();

	std::vector<std::shared_ptr<Geo2d_TopoChainAnalysis_Node>> nodes;
	nodes.reserve(points.size());

	{ // import the nodes [4/2/2022 Amir]
		Standard_Integer k = 0;
		for (const auto& x : points)
		{
			auto n = std::make_shared<Geo2d_TopoChainAnalysis_Node>(++k, x);
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

			auto e = std::make_shared<Geo2d_SegmentGraphEdge>(++k, nodes[Index_Of(v0)], nodes[Index_Of(v1)]);
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
#endif // _DEBUG

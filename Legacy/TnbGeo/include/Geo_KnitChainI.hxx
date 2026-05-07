#pragma once
#include <Knit_ChainNode.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class KnitTraits>
inline std::shared_ptr<typename tnbLib::Geo_KnitChain<KnitTraits>::nodeType>
tnbLib::Geo_KnitChain<KnitTraits>::Next(const std::shared_ptr<nodeType>& theNode)
{
	auto node = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(theNode);
	Debug_Null_Pointer(node);

	if (node->Type() NOT_EQUAL Knit_ChainNode_Type::regular)
	{
		if (NOT node->NbEdges())
		{
			knitReg::RemoveItem(node);
		}
		return nullptr;
	}

	auto edges = node->RetrieveEdges();

	auto edge = std::dynamic_pointer_cast<edgeType>(edges[0].lock());
	Debug_Null_Pointer(edge);

	node->RemoveFromEdges(edge->Index());
	knitReg::RemoveItem(edge);

	auto left = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(edge->Node0());
	auto right = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(edge->Node1());

	std::shared_ptr<nodeType> next;
	if (left IS_EQUAL node) next = right;
	else if (right IS_EQUAL node) next = left;
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to find the next node!" << endl
			<< abort(FatalError);
	}

	if (edges.size() IS_EQUAL 1)
	{
		knitReg::RemoveItem(node);
	}
	else
	{
		node->SetType(Knit_ChainNode_Type::start);
	}

	next->RemoveFromEdges(edge->Index());
	return std::move(next);
}

template<class KnitTraits>
inline std::shared_ptr<typename tnbLib::Geo_KnitChain<KnitTraits>::nodeType>
tnbLib::Geo_KnitChain<KnitTraits>::FindStart(const Knit_ChainNode_Type t) const
{
	const auto& nodes = knitReg::Nodes();
	for (const auto& x : nodes)
	{
		auto node = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(x.second);
		Debug_Null_Pointer(node);

		if (node->Type() IS_EQUAL t)
		{
			node->SetType(Knit_ChainNode_Type::start);
			return std::move(node);
		}
	}
	return nullptr;
}

template<class KnitTraits>
inline std::shared_ptr<typename tnbLib::Geo_KnitChain<KnitTraits>::polyType>
tnbLib::Geo_KnitChain<KnitTraits>::GetPolygon(const std::shared_ptr<nodeType>& theStart)
{
	auto current = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(theStart);
	Debug_Null_Pointer(current);

	current->SetType(Knit_ChainNode_Type::regular);

	auto polygon = std::make_shared<polyType>();
	Debug_Null_Pointer(polygon);

	auto& pts = polygon->Points();
	pts.push_back(current->Coord());
	auto next = Next(current);

	while (next)
	{
		pts.push_back(next->Coord());
		next = Next(next);
	}
	return std::move(polygon);
}

template<class KnitTraits>
inline void tnbLib::Geo_KnitChain<KnitTraits>::SetTypes()
{
	const auto& nodes = knitReg::Nodes();
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x.second);
		auto node = std::dynamic_pointer_cast<Knit_ChainNode<nodeType>>(x.second);
		Debug_Null_Pointer(node);

		if (node->NbEdges() IS_EQUAL 1)
		{
			// start node [1/4/2022 Amir]
			node->SetType(Knit_ChainNode_Type::start);
		}
		else
		{
			// regular node [1/4/2022 Amir]
			node->SetType(Knit_ChainNode_Type::regular);
		}
	}
}

//template<class KnitTraits>
//inline void tnbLib::Geo_KnitChain<KnitTraits>::Perform()
//{
//	std::vector<std::shared_ptr<polyType>> polygons;
//
//	// creating regular chains [1/5/2022 Amir]
//	auto start = FindStart(Knit_ChainNode_Type::start);
//	while (start)
//	{
//		auto poly = GetPolygon(start);
//		polygons.push_back(std::move(poly));
//
//		start = FindStart(Knit_ChainNode_Type::start);
//	}
//
//	// creating ring chains [1/5/2022 Amir]
//	if (knitReg::NbEdges())
//	{
//		start = FindStart(Knit_ChainNode_Type::regular);
//		while (start)
//		{
//			auto poly = GetPolygon(start);
//			polygons.push_back(std::move(poly));
//
//			start = FindStart(Knit_ChainNode_Type::regular);
//		}
//	}
//
//	if (knitReg::NbNodes())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the node tree is not empty." << endl
//			<< " - something went wrong!" << endl
//			<< abort(FatalError);
//	}
//
//	if (knitReg::NbEdges())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the edge tree is not empty." << endl
//			<< " - something went wrong!" << endl
//			<< abort(FatalError);
//	}
//
//	Change_IsDone() = Standard_True;
//}

template<class KnitTraits>
inline void tnbLib::Geo_KnitChain<KnitTraits>::Import
(
	const Entity_StaticData<Point, connectivity::dual>& theChain
)
{
	const auto& points = theChain.Points();
	const auto& indices = theChain.Connectivity();

	std::vector<std::shared_ptr<nodeType>> nodes;
	nodes.reserve(points.size());

	Standard_Integer nbNodes = 0;
	for (const auto& x : points)
	{
		auto n = std::make_shared<Knit_ChainNode<nodeType>>(++nbNodes, x);
		nodes.push_back(std::move(n));
	}

	Standard_Integer nbEdges = 0;
	for (const auto& x : indices)
	{
		auto v0 = x.Value(0);
		auto v1 = x.Value(1);

		auto e = std::make_shared<edgeType>(++nbEdges, nodes[Index_Of(v0)], nodes[Index_Of(v1)]);

		nodes[Index_Of(v0)]->InsertToEdges(e->Index(), e);
		nodes[Index_Of(v1)]->InsertToEdges(e->Index(), e);

		knitReg::Insert(std::move(e));
	}

	for (auto& x : nodes)
	{
		knitReg::Insert(std::move(x));
	}

	SetTypes();
}
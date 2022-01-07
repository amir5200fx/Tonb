#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::RemoveItem
(
	const std::shared_ptr<NodeType>& theNode
)
{
	auto iter = theNodes_.find(theNode->Index());
	if (iter IS_EQUAL theNodes_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not found in the tree!" << endl
			<< abort(FatalError);
	}
	theNodes_.erase(iter);
}

template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::RemoveItem
(
	const std::shared_ptr<EdgeType>& theEdge
)
{
	auto iter = theEdges_.find(theEdge->Index());
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not found in the tree!" << endl
			<< abort(FatalError);
	}
	theEdges_.erase(iter);
}

template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::Insert
(
	const std::shared_ptr<NodeType>& theNode
)
{
	auto paired = std::make_pair(theNode->Index(), theNode);
	auto insert = theNodes_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate item has been found!" << endl
			<< " - index: " << theNode->Index() << endl
			<< abort(FatalError);
	}
}

template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::Insert
(
	const std::shared_ptr<EdgeType>& theEdge
)
{
	auto paired = std::make_pair(theEdge->Index(), theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate item has been found!" << endl
			<< " - index: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}

template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::Insert
(
	std::shared_ptr<NodeType>&& theNode
)
{
	auto paired = std::make_pair(theNode->Index(), std::move(theNode));
	auto insert = theNodes_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate item has been found!" << endl
			<< " - index: " << theNode->Index() << endl
			<< abort(FatalError);
	}
}

template<class NodeType, class EdgeType>
inline void tnbLib::Knit_ChainRegistry<NodeType, EdgeType>::Insert
(
	std::shared_ptr<EdgeType>&& theEdge
)
{
	auto paired = std::make_pair(theEdge->Index(), std::move(theEdge));
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate item has been found!" << endl
			<< " - index: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}
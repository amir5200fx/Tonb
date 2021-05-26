#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class NodeType>
inline void tnbLib::Cad2d_RemoveNonManifold::Import
(
	std::shared_ptr<NodeType>&& theNode, 
	std::map<Standard_Integer, std::shared_ptr<NodeType>>& theMap
)
{
	auto paired = std::make_pair(theNode->Index(), std::move(theNode));
	auto insert = theMap.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " - index = " << theNode->Index() << endl
			<< abort(FatalError);
	}
}

template<class NodeType>
inline void tnbLib::Cad2d_RemoveNonManifold::Remove
(
	const std::shared_ptr<NodeType>& theNode, 
	std::map<Standard_Integer, std::shared_ptr<NodeType>>& theMap
)
{
	auto iter = theMap.find(theNode->Index());
	if (iter IS_EQUAL theMap.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theNode->Index() << endl
			<< abort(FatalError);
	}
	Debug_If_Condition(iter->second NOT_EQUAL theNode);
	theMap.erase(iter);
}
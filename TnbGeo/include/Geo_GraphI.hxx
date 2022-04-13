#pragma once
#include <Global_Tools.hxx>
template<class EdgeType>
inline void tnbLib::Geo_Graph<EdgeType>::Insert
(
	const Standard_Integer theIndex,
	const std::shared_ptr<EdgeType>& theEdge
)
{
	Global_Tools::Insert(theIndex, theEdge, theEdges_);
}

template<class EdgeType>
inline void tnbLib::Geo_Graph<EdgeType>::Insert
(
	const Standard_Integer theIndex,
	std::shared_ptr<EdgeType>&& theEdge
)
{
	Global_Tools::Insert(theIndex, std::move(theEdge), theEdges_);
}

template<class EdgeType>
inline void tnbLib::Geo_Graph<EdgeType>::Remove(const Standard_Integer theIndex)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("void Remove(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}

	edgeType::deAttach(theIndex);

	theEdges_.erase(iter);
}
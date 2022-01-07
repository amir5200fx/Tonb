#pragma once
template<class NodeTraits>
inline Standard_Boolean 
tnbLib::Geo_GraphNode<NodeTraits>::IsManifold() const
{
	return NbEdges() IS_EQUAL 2;
}

template<class NodeTraits>
inline Standard_Boolean 
tnbLib::Geo_GraphNode<NodeTraits>::IsBoundary() const
{
	return NbEdges() IS_EQUAL 1;
}

template<class NodeTraits>
inline Standard_Boolean 
tnbLib::Geo_GraphNode<NodeTraits>::IsOrphan() const
{
	return NOT NbEdges();
}

template<class NodeTraits>
inline std::vector<std::weak_ptr<typename tnbLib::Geo_GraphNode<NodeTraits>::edgeType>>
tnbLib::Geo_GraphNode<NodeTraits>::RetrieveEdges() const
{
	std::vector<std::weak_ptr<edgeType>> edges;
	edges.reserve(Edges().size());
	for (const auto& x : Edges())
	{
		edges.push_back(x.second);
	}
	return std::move(edges);
}

template<class NodeTraits>
inline void tnbLib::Geo_GraphNode<NodeTraits>::InsertToEdges
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<edgeType>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

template<class NodeTraits>
inline void tnbLib::Geo_GraphNode<NodeTraits>::InsertToEdges
(
	const Standard_Integer theIndex,
	std::shared_ptr<edgeType>&& theEdge
)
{
	auto paired = std::make_pair(theIndex, std::move(theEdge));
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

template<class NodeTraits>
inline void tnbLib::Geo_GraphNode<NodeTraits>::RemoveFromEdges
(
	const Standard_Integer theIndex
)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("void Remove(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}

	theEdges_.erase(iter);
}
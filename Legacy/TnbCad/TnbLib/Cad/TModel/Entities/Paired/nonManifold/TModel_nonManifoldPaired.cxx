#include <TModel_nonManifoldPaired.hxx>

#include <TModel_Edges.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::TModel_Edge>>
tnbLib::TModel_nonManifoldPaired::RetrieveEdges() const
{
	std::vector<std::shared_ptr<TModel_Edge>> edges;
	edges.reserve(NbEdges());
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x.second);
		edges.push_back(x.second);
	}
	return std::move(edges);
}

void tnbLib::TModel_nonManifoldPaired::RetrieveEdgesTo
(
	std::vector<std::shared_ptr<TModel_Edge>>& theEdges
) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x.second);
		theEdges.push_back(x.second);
	}
}

void tnbLib::TModel_nonManifoldPaired::SetPairs() const
{
	auto thisPaired = std::dynamic_pointer_cast<TModel_Paired>(std::const_pointer_cast<TModel_Entity>(This()));
	for (const auto& x : Edges())
	{
		const auto& edge = x.second;
		Debug_Null_Pointer(edge);

		auto g = std::dynamic_pointer_cast<TModel_GeneratedEdge>(edge);
		Debug_Null_Pointer(g);

		g->SetPaired(thisPaired);
	}
}

Standard_Boolean 
tnbLib::TModel_nonManifoldPaired::IsFree() const
{
	return theEdges_.size() IS_EQUAL 1;
}

std::shared_ptr<tnbLib::TModel_Edge> 
tnbLib::TModel_nonManifoldPaired::RemoveEdge
(
	const Standard_Integer theIndex
)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theEdges_.erase(iter);
	return std::move(item);
}

void tnbLib::TModel_nonManifoldPaired::InsertToEdges
(
	const Standard_Integer theIndex,
	const std::shared_ptr<TModel_Edge>& theEdge
)
{
	auto edge = theEdge;
	InsertToEdges(theIndex, std::move(edge));
}

void tnbLib::TModel_nonManifoldPaired::InsertToEdges
(
	const Standard_Integer theIndex,
	std::shared_ptr<TModel_Edge>&& theEdge
)
{
	auto paired = std::make_pair(theIndex, std::move(theEdge));
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}
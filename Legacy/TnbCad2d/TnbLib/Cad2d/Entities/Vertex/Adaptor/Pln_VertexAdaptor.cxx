#include <Pln_VertexAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::weak_ptr<tnbLib::Pln_Edge>> 
tnbLib::Pln_VertexAdaptor::RetrieveEdges() const
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);
	return std::move(edges);
}

void tnbLib::Pln_VertexAdaptor::InsertToEdges
(
	const Standard_Integer theIndex, 
	const std::weak_ptr<Pln_Edge>& theEdge
)
{
#ifdef _DEBUG
	auto iter = theEdges_.find(theIndex);
	if (iter NOT_EQUAL theEdges_.end())
	{
		FatalErrorIn("void InsertToEdges(const Standard_Integer theIndex, const std::weak_ptr<Pln_Edge>& theEdge)")
			<< "Duplicate data!" << endl
			<< abort(FatalError);
	}
#endif
	theEdges_.insert(std::make_pair(theIndex, theEdge));
}

void tnbLib::Pln_VertexAdaptor::RemoveFromEdges
(
	const Standard_Integer theIndex
)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("void RemoveFromEdges(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}

	theEdges_.erase(iter);
}

void tnbLib::Pln_VertexAdaptor::RetrieveEdgesTo
(
	std::vector<std::weak_ptr<Pln_Edge>>& theEdges
) const
{
	theEdges.reserve(theEdges_.size());
	for (const auto& x : theEdges_)
	{
		theEdges.push_back(x.second);
	}
}
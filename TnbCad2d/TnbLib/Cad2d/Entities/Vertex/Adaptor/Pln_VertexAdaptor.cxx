#include <Pln_VertexAdaptor.hxx>

#include <error.hxx>
#include <OSstream.hxx>

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
#include <Voyage_Node.hxx>

#include <Voyage_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Voyage_Node::ImportEdge(const std::shared_ptr<Voyage_Edge>& theEdge)
{
	auto paired = std::make_pair(theEdge->Index(), theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected." << endl
			<< " - id: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::Voyage_Node::RemoveEdge(const Standard_Integer theIndex)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " the item is not in the tree." << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	theEdges_.erase(iter);
}
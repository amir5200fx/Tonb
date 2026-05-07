#include <SectPx_TPntAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::weak_ptr<tnbLib::SectPx_Edge> 
tnbLib::SectPx_TPntAdaptor::RemoveFromEdges
(
	const Standard_Integer theIndex
)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theEdges_.erase(iter);
	return std::move(item);
}

void tnbLib::SectPx_TPntAdaptor::Import
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_Edge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
}
#include <Cad2d_Modeler_SelectList.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::cad2dLib::Modeler_SelectList::IsContain
(
	const Standard_Integer theIndex
) const
{
	auto iter = theItems_.find(theIndex);
	if (iter NOT_EQUAL theItems_.end())
	{
		return Standard_True;
	}
	return Standard_False;
}

std::weak_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_SelectList::Remove
(
	const Standard_Integer theIndex
)
{
	auto iter = theItems_.find(theIndex);
	if (iter IS_EQUAL theItems_.end())
	{
		FatalErrorIn("void Remove(const Standard_Integer theIndex)")
			<< "cannot remove the item from the tree: the item doesn't exist!" << endl
			<< abort(FatalError);
	}

	auto p = iter->second;
	theItems_.erase(iter);
	return std::move(p);
}

void tnbLib::cad2dLib::Modeler_SelectList::Import
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	auto insert = theItems_.insert(std::make_pair(theIndex, theEdge));
	if (NOT insert.second)
	{
		FatalErrorIn("void Import(const Standard_Integer theIndex, const std::shared_ptr<Pln_Edge>& theEdge)")
			<< "cannot insert the item into the tree: duplicate data!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::cad2dLib::Modeler_SelectList::Clear()
{
	theItems_.clear();
}

std::vector<std::weak_ptr<tnbLib::Pln_Edge>> 
tnbLib::cad2dLib::Modeler_SelectList::RetrieveItems() const
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveItemsTo(edges);

	return std::move(edges);
}

void tnbLib::cad2dLib::Modeler_SelectList::RetrieveItemsTo
(
	std::vector<std::weak_ptr<Pln_Edge>>& theItems
) const
{
	theItems.reserve(NbItems());
	for (const auto& x : theItems_)
	{
		theItems.push_back(x.second);
	}
}
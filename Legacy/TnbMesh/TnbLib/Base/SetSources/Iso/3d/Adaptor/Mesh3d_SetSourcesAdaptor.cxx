#include <Mesh3d_SetSourcesAdaptor.hxx>

#include <Mesh3d_Element.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::NbTets() const
{
	return (Standard_Integer)theTets_.size();
}

std::vector<std::shared_ptr<tnbLib::Mesh3d_Element>> 
tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::RetrieveTets() const
{
	std::vector<std::shared_ptr<Mesh3d_Element>> tets;
	RetrieveTetsTo(tets);
	return std::move(tets);
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::InsertToTets
(
	const std::shared_ptr<Mesh3d_Element>& theElement
)
{
	const auto id = theElement->Index();
	InsertToTets(id, theElement);
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::InsertToTets
(
	std::shared_ptr<Mesh3d_Element>&& theElement
)
{
	const auto id = theElement->Index();
	InsertToTets(id, std::move(theElement));
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::InsertToTets
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Mesh3d_Element>& theElement
)
{
	auto element = theElement;
	InsertToTets(theIndex, std::move(element));
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::InsertToTets
(
	const Standard_Integer theIndex, 
	std::shared_ptr<Mesh3d_Element>&& theElement
)
{
	auto paired = std::make_pair(theIndex, std::move(theElement));
	auto insert = theTets_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::RemoveFromTets
(
	const std::shared_ptr<Mesh3d_Element>& theElement
)
{
	RemoveFromTets(theElement->Index());
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::RemoveFromTets
(
	const Standard_Integer theIndex
)
{
	auto iter = theTets_.find(theIndex);
	if (iter IS_EQUAL theTets_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the map." << endl
			<< "- index: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::Geo3d_AttrbBalPrTreeLeaf_Adaptor<tnbLib::Mesh3d_Element>::RetrieveTetsTo
(
	std::vector<std::shared_ptr<Mesh3d_Element>>& theTets
) const
{
	theTets.reserve(NbTets());
	for (const auto& x : theTets_)
	{
		theTets.push_back(x.second);
	}
}
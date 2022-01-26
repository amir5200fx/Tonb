#include <Cad2d_IdentRings_NodeAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::IsOrphan() const
{
	return (Standard_Boolean)theLinks_.empty();
}

Standard_Boolean 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::IsManifold() const
{
	return (Standard_Boolean)(theLinks_.size() IS_EQUAL 2);
}

Standard_Boolean 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::IsDangle() const
{
	return (Standard_Boolean)(theLinks_.size() IS_EQUAL 1);
}

Standard_Boolean 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::Contains
(
	const Standard_Integer theIndex
) const
{
	auto iter = theLinks_.find(theIndex);
	if (iter IS_EQUAL theLinks_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

std::shared_ptr<tnbLib::cad2dLib::IdentRings_Link> 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::Remove
(
	const Standard_Integer theIndex
)
{
	auto iter = theLinks_.find(theIndex);
	if (iter IS_EQUAL theLinks_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = iter->second.lock();
	theLinks_.erase(iter);
	return std::move(item);
}

std::vector<std::shared_ptr<tnbLib::cad2dLib::IdentRings_Link>> 
tnbLib::cad2dLib::IdentRings_NodeAdaptor::RetrieveLinks() const
{
	std::vector<std::shared_ptr<IdentRings_Link>> links;
	links.reserve(NbLinks());
	for (const auto& x : theLinks_)
	{
		auto link = x.second.lock();
		links.push_back(std::move(link));
	}
	return std::move(links);
}

void tnbLib::cad2dLib::IdentRings_NodeAdaptor::Insert
(
	const Standard_Integer theIndex,
	const std::weak_ptr<IdentRings_Link>& theLink
)
{
	auto paired = std::make_pair(theIndex, theLink);
	auto insert = theLinks_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been found!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}
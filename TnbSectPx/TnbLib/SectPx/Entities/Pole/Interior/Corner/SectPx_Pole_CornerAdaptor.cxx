#include <SectPx_Pole_CornerAdaptor.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

std::weak_ptr<tnbLib::SectPx_PoleController> 
tnbLib::SectPx_Pole_CornerAdaptor::RemoveController
(
	const Standard_Integer theIndex
)
{
	auto iter = theControllers_.find(theIndex);
	if (iter IS_EQUAL theControllers_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theControllers_.erase(iter);
	return std::move(item);
}

void tnbLib::SectPx_Pole_CornerAdaptor::InsertToControllers
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<SectPx_PoleController>& theController
)
{
	auto paired = std::make_pair(theIndex, theController);
	auto insert = theControllers_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
}
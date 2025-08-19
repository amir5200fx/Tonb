#include <ShapePx_ParValue.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::ShapePx_ParValue::SetValue
(
	const Standard_Integer theParIndex, 
	const Standard_Real x
)
{
	auto paired = std::make_pair(theParIndex, x);
	auto insert = theValues_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - parameter index = " << theParIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::ShapePx_ParValue::Remove
(
	const Standard_Integer theParIndex
)
{
	auto iter = theValues_.find(theParIndex);
	if (iter IS_EQUAL theValues_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is not in the map" << endl
			<< abort(FatalError);
	}
	theValues_.erase(iter);
}
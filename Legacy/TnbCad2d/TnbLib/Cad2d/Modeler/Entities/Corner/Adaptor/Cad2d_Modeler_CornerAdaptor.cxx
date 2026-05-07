#include <Cad2d_Modeler_CornerAdaptor.hxx>

#include <Cad2d_Modeler_Segment.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::cad2dLib::Modeler_CornerAdaptor::IsContains
(
	const std::shared_ptr<Modeler_Segment>& theSegmnt
) const
{
	auto iter = theSegments_.find(theSegmnt->Index());
	if (iter IS_EQUAL theSegments_.end())
	{
		return Standard_False;
	}
	if (iter->second.lock() NOT_EQUAL theSegmnt)
	{
		return Standard_False;
	}
	return Standard_True;
}

std::weak_ptr<tnbLib::cad2dLib::Modeler_Segment> 
tnbLib::cad2dLib::Modeler_CornerAdaptor::RemoveFromSegments
(
	const Standard_Integer theIndex
)
{
	auto iter = theSegments_.find(theIndex);
	if (iter IS_EQUAL theSegments_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theSegments_.erase(iter);
	return std::move(item);
}

void tnbLib::cad2dLib::Modeler_CornerAdaptor::ImportToSegments
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Modeler_Segment>& theSegmnt
)
{
	auto paired = std::make_pair(theIndex, theSegmnt);
	auto insert = theSegments_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
}
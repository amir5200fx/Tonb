#include <Cad2d_Modeler_Segments.hxx>

#include <Cad2d_Modeler_Segment.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::cad2dLib::Modeler_Segments::InsertToSegments
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Modeler_Segment>& theSeg
)
{
	auto paired = std::make_pair(theIndex, theSeg);
	auto insert = theSegments_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " - index = "<< theIndex << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Segment> 
tnbLib::cad2dLib::Modeler_Segments::RemoveFromSegments
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

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Segments::IsContainsSegment
(
	const Standard_Integer theIndex
) const
{
	auto iter = theSegments_.find(theIndex);
	if (iter IS_EQUAL theSegments_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Segments::IsContainsSegment
(
	const std::shared_ptr<Modeler_Segment>& theSegmnt
) const
{
	Debug_Null_Pointer(theSegmnt);
	auto iter = theSegments_.find(theSegmnt->Index());
	if (iter IS_EQUAL theSegments_.end())
	{
		return Standard_False;
	}
	if (iter->second NOT_EQUAL theSegmnt)
	{
		return Standard_False;
	}
	return Standard_True;
}
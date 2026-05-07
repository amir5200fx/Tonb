#include <Cad2d_Modeler_Segment.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::cad2dLib::Modeler_Segment::Modeler_Segment
(
	const std::shared_ptr<Modeler_Corner>& theC0, 
	const std::shared_ptr<Modeler_Corner>& theC1
)
	: theCrn0_(theC0)
	, theCrn1_(theC1)
{
	// empty body
}

tnbLib::cad2dLib::Modeler_Segment::Modeler_Segment
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Modeler_Corner>& theC0,
	const std::shared_ptr<Modeler_Corner>& theC1
)
	: Modeler_Entity(theIndex)
	, theCrn0_(theC0)
	, theCrn1_(theC1)
{
	// empty body
}

tnbLib::cad2dLib::Modeler_Segment::Modeler_Segment
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Modeler_Corner>& theC0,
	const std::shared_ptr<Modeler_Corner>& theC1
)
	: Modeler_Entity(theIndex, theName)
	, theCrn0_(theC0)
	, theCrn1_(theC1)
{
	// empty body
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner> 
tnbLib::cad2dLib::Modeler_Segment::Other
(
	const std::shared_ptr<Modeler_Corner>& theCrn
) const
{
	if (theCrn IS_EQUAL Crn0())
	{
		return Crn1();
	}
	else if (theCrn IS_EQUAL Crn1())
	{
		return Crn0();
	}
	FatalErrorIn(FunctionSIG)
		<< "the corner is not belong to the segment" << endl
		<< abort(FatalError);
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Segment::RemoveFromEdges
(
	const Standard_Integer theIndex
) 
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theEdges_.erase(iter);
	return std::move(item);
}

void tnbLib::cad2dLib::Modeler_Segment::ImportToEdges
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
}

tnbLib::cad2dLib::Modeler_Ring::Modeler_Ring
(
	const std::shared_ptr<Modeler_Corner>& theCrn
)
	: Modeler_Segment(theCrn, theCrn)
{
	// empty body
}

tnbLib::cad2dLib::Modeler_Ring::Modeler_Ring
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Modeler_Corner>& theCrn
)
	: Modeler_Segment(theIndex, theCrn, theCrn)
{
	// empty body
}

tnbLib::cad2dLib::Modeler_Ring::Modeler_Ring
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<Modeler_Corner>& theCrn
)
	: Modeler_Segment(theIndex, theName, theCrn, theCrn)
{
	// empty body
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>
tnbLib::cad2dLib::Modeler_Ring::Other
(
	const std::shared_ptr<Modeler_Corner>& theCrn
) const
{
	return theCrn;
}
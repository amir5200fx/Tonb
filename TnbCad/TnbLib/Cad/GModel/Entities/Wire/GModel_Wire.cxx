#include <GModel_Wire.hxx>

tnbLib::GModel_Wire::GModel_Wire
(
	const std::shared_ptr<edgeList>& theEdges
)
	: theEdges_(theEdges)
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	std::shared_ptr<edgeList>&& theEdges
)
	: theEdges_(std::move(theEdges))
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<edgeList>& theEdges
)
	: GModel_Entity(theIndex, theName)
{
	//- empty body
}

tnbLib::GModel_Wire::GModel_Wire
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<edgeList>&& theEdges
)
	: GModel_Entity(theIndex, theName)
	, theEdges_(theEdges)
{
	//- empty body
}

Standard_Integer 
tnbLib::GModel_Wire::NbEdges() const
{
	return (Standard_Integer)theEdges_->size();
}
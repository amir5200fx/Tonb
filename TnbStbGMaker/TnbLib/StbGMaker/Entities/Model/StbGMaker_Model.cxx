#include <StbGMaker_Model.hxx>

tnbLib::StbGMaker_Model::StbGMaker_Model
(
	const Standard_Integer theIndex
)
	: StbGMaker_Entity(theIndex)
{
	// empty body
}

tnbLib::StbGMaker_Model::StbGMaker_Model
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: StbGMaker_Entity(theIndex, theName)
{
	// empty body
}
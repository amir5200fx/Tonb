#include <Marine_Model.hxx>

tnbLib::Marine_Model::Marine_Model()
{
}

tnbLib::Marine_Model::Marine_Model
(
	const Standard_Integer theIndex
)
	: Marine_Entity(theIndex)
{
}

tnbLib::Marine_Model::Marine_Model
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
}
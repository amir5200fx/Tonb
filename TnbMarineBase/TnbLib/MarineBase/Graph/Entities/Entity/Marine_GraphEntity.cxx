#include <Marine_GraphEntity.hxx>

tnbLib::Marine_GraphEntity::Marine_GraphEntity()
{
}

tnbLib::Marine_GraphEntity::Marine_GraphEntity
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::Marine_GraphEntity::Marine_GraphEntity
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}
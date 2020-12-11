#include <NModel_Entity.hxx>

tnbLib::NModel_Entity::NModel_Entity
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
	// empty body
}

tnbLib::NModel_Entity::NModel_Entity
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
	// empty body
}
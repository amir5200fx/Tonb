#include <HydStatic_Entity.hxx>

tnbLib::HydStatic_Entity::HydStatic_Entity()
{
}

tnbLib::HydStatic_Entity::HydStatic_Entity
(
	const Standard_Integer theIndex
)
	: Global_Indexed(theIndex)
{
}

tnbLib::HydStatic_Entity::HydStatic_Entity
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}
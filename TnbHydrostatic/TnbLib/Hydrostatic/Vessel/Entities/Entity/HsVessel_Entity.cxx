#include <HsVessel_Entity.hxx>

tnbLib::HsVessel_Entity::HsVessel_Entity()
	: Global_Named("HsVessel_Entity")
{
}

tnbLib::HsVessel_Entity::HsVessel_Entity
(
	const Standard_Integer theIndex
)
	: Global_Named("HsVessel_Entity")
	, Global_Indexed(theIndex)
{
}

tnbLib::HsVessel_Entity::HsVessel_Entity
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
{
}
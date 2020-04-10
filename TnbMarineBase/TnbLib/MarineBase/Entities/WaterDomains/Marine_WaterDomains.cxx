#include <Marine_WaterDomains.hxx>

tnbLib::Marine_WaterDomains::Marine_WaterDomains()
{
}

tnbLib::Marine_WaterDomains::Marine_WaterDomains
(
	const Standard_Integer theIndex
)
	: Marine_Entity(theIndex)
{
}

tnbLib::Marine_WaterDomains::Marine_WaterDomains
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
}
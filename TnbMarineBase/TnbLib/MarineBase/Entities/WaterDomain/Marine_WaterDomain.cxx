#include <Marine_WaterDomain.hxx>

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: theDomain_(theDomain)
{
}

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Marine_Entity(theIndex)
	, theDomain_(theDomain)
{
}

tnbLib::Marine_WaterDomain::Marine_WaterDomain
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Marine_Entity(theIndex, theName)
	, theDomain_(theDomain)
{
}
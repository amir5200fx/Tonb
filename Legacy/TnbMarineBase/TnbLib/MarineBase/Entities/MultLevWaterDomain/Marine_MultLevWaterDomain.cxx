#include <Marine_MultLevWaterDomain.hxx>

tnbLib::Marine_MultLevWaterDomain::Marine_MultLevWaterDomain
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_Entity(theIndex, theName)
{
	// empty body
}

tnbLib::Marine_MultLevWaterDomain::Marine_MultLevWaterDomain
(
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<Marine_Body>& theBody,
	const std::vector<std::shared_ptr<Marine_WaterDomain>>& theDomains
)
	: theDomain_(theDomain)
	, theBody_(theBody)
	, theWaters_(theDomains)
{
	// empty body
}

tnbLib::Marine_MultLevWaterDomain::Marine_MultLevWaterDomain
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<Marine_Body>& theBody, 
	const std::vector<std::shared_ptr<Marine_WaterDomain>>& theDomains
)
	: Marine_Entity(theIndex, theName)
	, theDomain_(theDomain)
	, theBody_(theBody)
	, theWaters_(theDomains)
{
	// empty body
}

tnbLib::Marine_MultLevWaterDomain::Marine_MultLevWaterDomain
(
	std::shared_ptr<Marine_Domain>&& theDomain,
	std::shared_ptr<Marine_Body>&& theBody, 
	std::vector<std::shared_ptr<Marine_WaterDomain>>&& theDomains
)
	: theDomain_(std::move(theDomain))
	, theBody_(std::move(theBody))
	, theWaters_(std::move(theDomains))
{
	// empty body
}

tnbLib::Marine_MultLevWaterDomain::Marine_MultLevWaterDomain
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<Marine_Domain>&& theDomain,
	std::shared_ptr<Marine_Body>&& theBody,
	std::vector<std::shared_ptr<Marine_WaterDomain>>&& theDomains
)
	: Marine_Entity(theIndex, theName)
	, theDomain_(std::move(theDomain))
	, theBody_(std::move(theBody))
	, theWaters_(std::move(theDomains))
{
	// empty body
}
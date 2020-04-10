#include <Marine_WaterDomain_Still.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_Body.hxx>
#include <Marine_Domain.hxx>
#include <MarineBase_Tools.hxx>

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theZ
)
	: Marine_WaterDomain(theDomain)
	, theZ_(theZ)
{
}

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theZ
)
	: Marine_WaterDomain(theIndex, theDomain)
	, theZ_(theZ)
{
}

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const Standard_Real theZ
)
	: Marine_WaterDomain(theIndex, theName, theDomain)
	, theZ_(theZ)
{
}

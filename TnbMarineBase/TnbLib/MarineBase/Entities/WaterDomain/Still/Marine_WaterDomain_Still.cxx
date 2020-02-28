#include <Marine_WaterDomain_Still.hxx>

#include <Marine_CmpSection.hxx>
#include <Marine_Body.hxx>
#include <Marine_Domain.hxx>
#include <MarineBase_Tools.hxx>

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Marine_WaterDomain(theDomain)
{
}

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Marine_WaterDomain(theIndex, theDomain)
{
}

tnbLib::Marine_WaterDomain_Still::Marine_WaterDomain_Still
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<Marine_Domain>& theDomain
)
	: Marine_WaterDomain(theIndex, theName, theDomain)
{
}

void tnbLib::Marine_WaterDomain_Still::Perform
(
	const Marine_Body & theModel, 
	const Standard_Real z
)
{
	Perform(theModel.Sections(), z);
}

void tnbLib::Marine_WaterDomain_Still::Perform
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
	const Standard_Real z
)
{
	ChangeZ() = z;

	ChangeWaters() = MarineBase_Tools::StillWaterSections(theModel, z, Domain()->Dim());
	Change_IsDone() = Standard_True;
}
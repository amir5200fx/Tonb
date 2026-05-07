#include <PtdModel_PropHub.hxx>

tnbLib::PtdModel_PropHub::PtdModel_PropHub
(
	const std::shared_ptr<PtdModel_PropBlade>& theBlade, 
	const std::shared_ptr<PtdModel_PropHubPars>& thePars, 
	const std::shared_ptr<PtdModel_PropHubSection>& theSection
)
	: theBlade_(theBlade)
	, theParameters_(thePars)
	, theSection_(theSection)
{
	//- empty body
}

tnbLib::PtdModel_PropHub::PtdModel_PropHub
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<PtdModel_PropBlade>& theBlade, 
	const std::shared_ptr<PtdModel_PropHubPars>& thePars,
	const std::shared_ptr<PtdModel_PropHubSection>& theSection
)
	: PtdModel_Entity(theIndex, theName)
	, theBlade_(theBlade)
	, theParameters_(thePars)
	, theSection_(theSection)
{
	//- empty body
}

void tnbLib::PtdModel_PropHub::Perform()
{
	Revolve();

	Change_IsDone() = Standard_True;
}

void tnbLib::PtdModel_PropHub::LoadBlade(const std::shared_ptr<PtdModel_PropBlade>& theBlade)
{
	theBlade_ = theBlade;
}

void tnbLib::PtdModel_PropHub::LoadParameters(const std::shared_ptr<PtdModel_PropHubPars>& thePars)
{
	theParameters_ = thePars;
}

void tnbLib::PtdModel_PropHub::LoadSection(const std::shared_ptr<PtdModel_PropHubSection>& theSection)
{
	theSection_ = theSection;
}
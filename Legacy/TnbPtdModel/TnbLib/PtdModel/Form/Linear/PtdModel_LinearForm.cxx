#include <PtdModel_LinearForm.hxx>

tnbLib::PtdModel_LinearForm::PtdModel_LinearForm
(
	const std::shared_ptr<PtdModel_Par>& theX0,
	const std::shared_ptr<PtdModel_Par>& theX1
)
	: theX0_(theX0)
	, theX1_(theX1)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::PtdModel_LinearForm::PtdModel_LinearForm
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<PtdModel_Par>& theX0, 
	const std::shared_ptr<PtdModel_Par>& theX1
)
	: PtdModel_Form(theIndex, theName)
	, theX0_(theX0)
	, theX1_(theX1)
{
	// empty body [6/3/2021 Amir]
}

Standard_Integer 
tnbLib::PtdModel_LinearForm::NbParameters() const
{
	return 2;
}

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_LinearForm::Parameters() const
{
	auto reg = RetrieveMap(const_cast<std::shared_ptr<PtdModel_Par>*>(&theX0_), NbParameters());
	return std::move(reg);
}
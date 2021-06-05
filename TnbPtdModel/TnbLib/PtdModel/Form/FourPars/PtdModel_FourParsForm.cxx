#include <PtdModel_FourParsForm.hxx>

tnbLib::PtdModel_FourParsForm::PtdModel_FourParsForm
(
	const std::shared_ptr<PtdModel_Par>& theX0,
	const std::shared_ptr<PtdModel_Par>& theX1,
	const std::shared_ptr<PtdModel_Par>& theX2, 
	const std::shared_ptr<PtdModel_Par>& theX3
)
	: theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
	, theX3_(theX3)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::PtdModel_FourParsForm::PtdModel_FourParsForm
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<PtdModel_Par>& theX0,
	const std::shared_ptr<PtdModel_Par>& theX1,
	const std::shared_ptr<PtdModel_Par>& theX2, 
	const std::shared_ptr<PtdModel_Par>& theX3
)
	: PtdModel_Form(theIndex, theName)
	, theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
	, theX3_(theX3)
{
	// empty body [6/3/2021 Amir]
}

Standard_Integer 
tnbLib::PtdModel_FourParsForm::NbParameters() const
{
	return 4;
}

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_FourParsForm::Parameters() const
{
	auto reg = RetrieveMap(const_cast<std::shared_ptr<PtdModel_Par>*>(&theX0_), NbParameters());
	return std::move(reg);
}
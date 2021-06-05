#include <PtdModel_FiveParsForm.hxx>

tnbLib::PtdModel_FiveParsForm::PtdModel_FiveParsForm
(
	const std::shared_ptr<PtdModel_Par>& theX0,
	const std::shared_ptr<PtdModel_Par>& theX1,
	const std::shared_ptr<PtdModel_Par>& theX2, 
	const std::shared_ptr<PtdModel_Par>& theX3, 
	const std::shared_ptr<PtdModel_Par>& theX4
)
	: theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
	, theX3_(theX3)
	, theX4_(theX4)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::PtdModel_FiveParsForm::PtdModel_FiveParsForm
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<PtdModel_Par>& theX0,
	const std::shared_ptr<PtdModel_Par>& theX1,
	const std::shared_ptr<PtdModel_Par>& theX2,
	const std::shared_ptr<PtdModel_Par>& theX3,
	const std::shared_ptr<PtdModel_Par>& theX4
)
	: PtdModel_Form(theIndex, theName)
	, theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
	, theX3_(theX3)
	, theX4_(theX4)
{
	// empty body [6/3/2021 Amir]
}

Standard_Integer 
tnbLib::PtdModel_FiveParsForm::NbParameters() const
{
	return 5;
}

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_FiveParsForm::Parameters() const
{
	auto reg = RetrieveMap(const_cast<std::shared_ptr<PtdModel_Par>*>(&theX0_), NbParameters());
	return std::move(reg);
}
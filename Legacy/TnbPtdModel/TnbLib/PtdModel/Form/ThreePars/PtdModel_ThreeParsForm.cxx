#include <PtdModel_ThreeParsForm.hxx>

tnbLib::PtdModel_ThreeParsForm::PtdModel_ThreeParsForm
(
	const std::shared_ptr<PtdModel_Par>& theX0, 
	const std::shared_ptr<PtdModel_Par>& theX1,
	const std::shared_ptr<PtdModel_Par>& theX2
)
	: theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::PtdModel_ThreeParsForm::PtdModel_ThreeParsForm
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<PtdModel_Par>& theX0, 
	const std::shared_ptr<PtdModel_Par>& theX1, 
	const std::shared_ptr<PtdModel_Par>& theX2
)
	: PtdModel_Form(theIndex, theName)
	, theX0_(theX0)
	, theX1_(theX1)
	, theX2_(theX2)
{
	// empty body [6/3/2021 Amir]
}

Standard_Integer
tnbLib::PtdModel_ThreeParsForm::NbParameters() const
{
	return 3;
}

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_ThreeParsForm::Parameters() const
{
	auto reg = RetrieveMap(const_cast<std::shared_ptr<PtdModel_Par>*>(&theX0_), NbParameters());
	return std::move(reg);
}
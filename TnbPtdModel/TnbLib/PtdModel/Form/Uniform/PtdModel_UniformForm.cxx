#include <PtdModel_UniformForm.hxx>

#include <PtdModel_Par.hxx>

tnbLib::PtdModel_UniformForm::PtdModel_UniformForm
(
	const std::shared_ptr<PtdModel_Par>& x
)
	: theValue_(x)
{
	// empty body [6/3/2021 Amir]
}

tnbLib::PtdModel_UniformForm::PtdModel_UniformForm
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<PtdModel_Par>& x
)
	: PtdModel_Form(theIndex, theName)
{
	// empty body [6/3/2021 Amir]
}

Standard_Integer 
tnbLib::PtdModel_UniformForm::NbParameters() const
{
	return 1;
}

std::map<tnbLib::word, std::shared_ptr<tnbLib::PtdModel_Par>> 
tnbLib::PtdModel_UniformForm::Parameters() const
{
	std::map<word, std::shared_ptr<PtdModel_Par>> reg;
	auto paired = std::make_pair(theValue_->Name(), theValue_);
	auto insert = reg.insert(std::move(paired));
	return std::move(reg);
}

void tnbLib::PtdModel_UniformForm::SetValue(std::shared_ptr<PtdModel_Par>&& p)
{
	theValue_ = std::move(p);
}
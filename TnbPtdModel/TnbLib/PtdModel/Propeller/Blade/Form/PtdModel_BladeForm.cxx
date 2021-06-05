#include <PtdModel_BladeForm.hxx>

#include <PtdModel_Form.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::PtdModel_BladeForm::Import
(
	const std::shared_ptr<PtdModel_Form>& theForm
)
{
	Debug_Null_Pointer(theForm);

	auto paired = std::make_pair(theForm->Name(), theForm);
	auto insert = theForms_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected!" << endl
			<< " - name: " << theForm->Name() << endl
			<< abort(FatalError);
	}
}

void tnbLib::PtdModel_BladeForm::Import
(
	std::shared_ptr<PtdModel_Form>&& theForm
)
{
	Debug_Null_Pointer(theForm);

	auto paired = std::make_pair(theForm->Name(), std::move(theForm));
	auto insert = theForms_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
}
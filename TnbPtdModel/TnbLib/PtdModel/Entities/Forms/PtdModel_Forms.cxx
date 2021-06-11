#include <PtdModel_Forms.hxx>

#include <PtdModel_Form.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::PtdModel_Forms::Import
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

void tnbLib::PtdModel_Forms::Import
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
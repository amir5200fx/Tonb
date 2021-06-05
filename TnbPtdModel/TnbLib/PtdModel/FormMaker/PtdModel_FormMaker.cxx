#include <PtdModel_FormMaker.hxx>

#include <PtdModel_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::PtdModel_Par>
tnbLib::PtdModel_FormMaker::Parameter(const word & name) const
{
	auto iter = theParameters_.find(name);
	if (iter IS_EQUAL theParameters_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to find the parameter!" << endl
			<< " -name: " << name << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::vector<tnbLib::word>
tnbLib::PtdModel_FormMaker::RetrieveParameters() const
{
	std::vector<word> parameters;
	parameters.reserve(NbParameters());
	for (size_t i = 0; i < NbParameters(); i++)
	{
		parameters.push_back(Parameter(i));
	}
	return std::move(parameters);
}

void tnbLib::PtdModel_FormMaker::SetParameter
(
	const word & name,
	const std::shared_ptr<PtdModel_Par>& par
)
{
	par->SetName(name);
	auto paired = std::make_pair(name, par);
	auto insert = theParameters_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected during parameter registration!" << endl
			<< "-name: " << name << endl
			<< abort(FatalError);
	}
}

void tnbLib::PtdModel_FormMaker::SetParameter
(
	const word & name,
	std::shared_ptr<PtdModel_Par>&& par
)
{
	par->SetName(name);
	auto paired = std::make_pair(name, std::move(par));
	auto insert = theParameters_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected during parameter registration!" << endl
			<< "-name: " << name << endl
			<< abort(FatalError);
	}
}
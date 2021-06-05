#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>

inline std::shared_ptr<tnbLib::PtdModel_Par>
tnbLib::PtdModel_Parameters::SelectParameter(const word & name) const
{
	auto iter = theParameters_.find(name);
	if (iter IS_EQUAL theParameters_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is not found!" << endl
			<< " - name: " << name << endl
			<< abort(FatalError);
	}
	return iter->second;
}
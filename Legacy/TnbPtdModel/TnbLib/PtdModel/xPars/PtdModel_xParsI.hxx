#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
inline Standard_Integer 
tnbLib::PtdModel_xPars::NbParameters() const
{
	return (Standard_Integer)theParameters_.size();
}

inline Standard_Integer 
tnbLib::PtdModel_xPars::NbSections() const
{
	return (Standard_Integer)theX_.size();
}

inline std::shared_ptr<typename tnbLib::PtdModel_xPars::realList>
tnbLib::PtdModel_xPars::SelectParameter(const word & name) const
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

inline void tnbLib::PtdModel_xPars::SetXs(realList && xs)
{
	theX_ = std::move(xs);
}

inline void tnbLib::PtdModel_xPars::SetParameter
(
	const word & theName,
	std::shared_ptr<realList>&& x
)
{
	auto paired = std::make_pair(theName, std::move(x));
	auto insert = theParameters_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< "- name: " << theName << endl
			<< abort(FatalError);
	}
}
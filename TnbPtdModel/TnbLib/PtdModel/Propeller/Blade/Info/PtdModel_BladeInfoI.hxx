#pragma once
inline void tnbLib::PtdModel_BladeInfo::SetNbSections(const Standard_Integer n)
{
	theNbSections_ = n;
}

inline void tnbLib::PtdModel_BladeInfo::SetNbSpans(const Standard_Integer n)
{
	theNbSpans_ = n;
}

inline void tnbLib::PtdModel_BladeInfo::SetBladeForm(const std::shared_ptr<PtdModel_BladeForm>& form)
{
	theBladeForm_ = form;
}

inline void tnbLib::PtdModel_BladeInfo::SetBladeForm(std::shared_ptr<PtdModel_BladeForm>&& form)
{
	theBladeForm_ = std::move(form);
}

inline void tnbLib::PtdModel_BladeInfo::SetGlobals(const std::shared_ptr<PtdModel_BladeGlobalPars>& pars)
{
	theGlobals_ = pars;
}

inline void tnbLib::PtdModel_BladeInfo::SetGlobals(std::shared_ptr<PtdModel_BladeGlobalPars>&& pars)
{
	theGlobals_ = std::move(pars);
}
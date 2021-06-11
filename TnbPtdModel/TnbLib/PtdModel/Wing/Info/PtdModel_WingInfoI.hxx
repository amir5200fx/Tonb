#pragma once
inline void tnbLib::PtdModel_WingInfo::SetNbSections(const Standard_Integer n)
{
	theNbSections_ = n;
}

inline void tnbLib::PtdModel_WingInfo::SetNbSpans(const Standard_Integer n)
{
	theNbSpans_ = n;
}

inline void tnbLib::PtdModel_WingInfo::SetForms(const std::shared_ptr<PtdModel_Forms>& forms)
{
	theForms_ = forms;
}

inline void tnbLib::PtdModel_WingInfo::SetForms(std::shared_ptr<PtdModel_Forms>&& forms)
{
	theForms_ = std::move(forms);
}

inline void tnbLib::PtdModel_WingInfo::SetLength(const std::shared_ptr<PtdModel_WingGlobalPars>& pars)
{
	theGlobals_ = pars;
}

inline void tnbLib::PtdModel_WingInfo::SetLength(std::shared_ptr<PtdModel_WingGlobalPars>&& pars)
{
	theGlobals_ = std::move(pars);
}
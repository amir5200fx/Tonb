#pragma once
inline void tnbLib::PtdModel_WingGlobalPars::SetSpanLength(const std::shared_ptr<PtdModel_Par>& par)
{
	theSpan_ = par;
}

inline void tnbLib::PtdModel_WingGlobalPars::SetSpanLength(std::shared_ptr<PtdModel_Par>&& par)
{
	theSpan_ = std::move(par);
}
#pragma once
inline void tnbLib::PtdModel_BladeGlobalPars::SetDiameter(const std::shared_ptr<PtdModel_Par>& p)
{
	theDiameter_ = p;
}

inline void tnbLib::PtdModel_BladeGlobalPars::SetDiameter(std::shared_ptr<PtdModel_Par>&& p)
{
	theDiameter_ = std::move(p);
}

inline void tnbLib::PtdModel_BladeGlobalPars::SetHubRadius(const std::shared_ptr<PtdModel_Par>& p)
{
	theHubRadius_ = p;
}

inline void tnbLib::PtdModel_BladeGlobalPars::SetHubRadius(std::shared_ptr<PtdModel_Par>&& p)
{
	theHubRadius_ = std::move(p);
}
#pragma once
inline void tnbLib::PtdModel_LinearForm::SetX(const Standard_Integer i, std::shared_ptr<PtdModel_Par>&& p)
{
	(&theX0_)[i] = std::move(p);
}

inline void tnbLib::PtdModel_LinearForm::SetX(const Standard_Integer i, const std::shared_ptr<PtdModel_Par>& p)
{
	(&theX0_)[i] = p;
}
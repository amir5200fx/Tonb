#pragma once
inline void tnbLib::PtdModel_FourParsForm::SetX0(std::shared_ptr<PtdModel_Par>&& p)
{
	theX0_ = std::move(p);
}

inline void tnbLib::PtdModel_FourParsForm::SetX1(std::shared_ptr<PtdModel_Par>&& p)
{
	theX1_ = std::move(p);
}

inline void tnbLib::PtdModel_FourParsForm::SetX2(std::shared_ptr<PtdModel_Par>&& p)
{
	theX2_ = std::move(p);
}

inline void tnbLib::PtdModel_FourParsForm::SetX3(std::shared_ptr<PtdModel_Par>&& p)
{
	theX3_ = std::move(p);
}

inline void tnbLib::PtdModel_FourParsForm::SetX0(const std::shared_ptr<PtdModel_Par>& p)
{
	theX0_ = p;
}

inline void tnbLib::PtdModel_FourParsForm::SetX1(const std::shared_ptr<PtdModel_Par>& p)
{
	theX1_ = p;
}

inline void tnbLib::PtdModel_FourParsForm::SetX2(const std::shared_ptr<PtdModel_Par>& p)
{
	theX2_ = p;
}

inline void tnbLib::PtdModel_FourParsForm::SetX3(const std::shared_ptr<PtdModel_Par>& p)
{
	theX3_ = p;
}

inline void tnbLib::PtdModel_FourParsForm::SetX(const Standard_Integer i, std::shared_ptr<PtdModel_Par>&& p)
{
	(&theX0_)[i] = std::move(p);
}

inline void tnbLib::PtdModel_FourParsForm::SetX(const Standard_Integer i, const std::shared_ptr<PtdModel_Par>& p)
{
	(&theX0_)[i] = p;
}
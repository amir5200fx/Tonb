#pragma once
inline void tnbLib::PtdModel_SixParsForm::SetX0(std::shared_ptr<PtdModel_Par>&& p)
{
	theX0_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX1(std::shared_ptr<PtdModel_Par>&& p)
{
	theX1_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX2(std::shared_ptr<PtdModel_Par>&& p)
{
	theX2_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX3(std::shared_ptr<PtdModel_Par>&& p)
{
	theX3_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX4(std::shared_ptr<PtdModel_Par>&& p)
{
	theX4_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX5(std::shared_ptr<PtdModel_Par>&& p)
{
	theX5_ = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX0(const std::shared_ptr<PtdModel_Par>& p)
{
	theX0_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX1(const std::shared_ptr<PtdModel_Par>& p)
{
	theX1_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX2(const std::shared_ptr<PtdModel_Par>& p)
{
	theX2_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX3(const std::shared_ptr<PtdModel_Par>& p)
{
	theX3_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX4(const std::shared_ptr<PtdModel_Par>& p)
{
	theX4_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX5(const std::shared_ptr<PtdModel_Par>& p)
{
	theX5_ = p;
}

inline void tnbLib::PtdModel_SixParsForm::SetX(const Standard_Integer i, std::shared_ptr<PtdModel_Par>&& p)
{
	(&theX0_)[i] = std::move(p);
}

inline void tnbLib::PtdModel_SixParsForm::SetX(const Standard_Integer i, const std::shared_ptr<PtdModel_Par>& p)
{
	(&theX0_)[i] = p;
}
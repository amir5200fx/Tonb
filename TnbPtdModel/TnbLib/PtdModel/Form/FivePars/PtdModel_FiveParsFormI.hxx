#pragma once
inline void tnbLib::PtdModel_FiveParsForm::SetX0(std::shared_ptr<PtdModel_Par>&& p)
{
	theX0_ = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX1(std::shared_ptr<PtdModel_Par>&& p)
{
	theX1_ = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX2(std::shared_ptr<PtdModel_Par>&& p)
{
	theX2_ = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX3(std::shared_ptr<PtdModel_Par>&& p)
{
	theX3_ = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX4(std::shared_ptr<PtdModel_Par>&& p)
{
	theX4_ = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX0(const std::shared_ptr<PtdModel_Par>& p)
{
	theX0_ = p;
}

inline void tnbLib::PtdModel_FiveParsForm::SetX1(const std::shared_ptr<PtdModel_Par>& p)
{
	theX1_ = p;
}

inline void tnbLib::PtdModel_FiveParsForm::SetX2(const std::shared_ptr<PtdModel_Par>& p)
{
	theX2_ = p;
}

inline void tnbLib::PtdModel_FiveParsForm::SetX3(const std::shared_ptr<PtdModel_Par>& p)
{
	theX3_ = p;
}

inline void tnbLib::PtdModel_FiveParsForm::SetX4(const std::shared_ptr<PtdModel_Par>& p)
{
	theX4_ = p;
}

inline void tnbLib::PtdModel_FiveParsForm::SetX(const Standard_Integer id, std::shared_ptr<PtdModel_Par>&& p)
{
	(&theX0_)[id] = std::move(p);
}

inline void tnbLib::PtdModel_FiveParsForm::SetX(const Standard_Integer id, const std::shared_ptr<PtdModel_Par>& p)
{
	(&theX0_)[id] = p;
}
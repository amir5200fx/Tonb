#pragma once
inline void tnbLib::ptdModel::SolidMaker_PropBlade::LoadBlade(const std::shared_ptr<PtdModel_PropBlade>& theBlade)
{
	theBlade_ = theBlade;
}

inline void tnbLib::ptdModel::SolidMaker_PropBlade::LoadBlade(std::shared_ptr<PtdModel_PropBlade>&& theBlade)
{
	theBlade_ = std::move(theBlade);
}

inline void tnbLib::ptdModel::SolidMaker_PropBlade::SetTolerance(const Standard_Real theTol)
{
	theTolerance_ = theTol;
}

inline void tnbLib::ptdModel::SolidMaker_PropBlade::SetToCreateLeadingPatch(const Standard_Boolean create)
{
	hasLeadingPatch_ = create;
}

inline void tnbLib::ptdModel::SolidMaker_PropBlade::SetToCreateTrailingPatch(const Standard_Boolean create)
{
	hasTrailingPatch_ = create;
}
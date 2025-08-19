#pragma once

inline Standard_Integer 
tnbLib::PtdModel_BladeExpandedView::NbSpans() const
{
	return (Standard_Integer)theX_.size();
}

inline void tnbLib::PtdModel_BladeExpandedView::SetX(std::vector<Standard_Real>&& x)
{
	theX_ = std::move(x);
}

inline void tnbLib::PtdModel_BladeExpandedView::SetXs(std::vector<Standard_Real>&& x)
{
	theXs_ = std::move(x);
}

inline void tnbLib::PtdModel_BladeExpandedView::SetTf(std::vector<Standard_Real>&& x)
{
	theTf_ = std::move(x);
}

inline void tnbLib::PtdModel_BladeExpandedView::SetTb(std::vector<Standard_Real>&& x)
{
	theTb_ = std::move(x);
}

inline void tnbLib::PtdModel_BladeExpandedView::SetYf(std::vector<Standard_Real>&& x)
{
	theYf_ = std::move(x);
}

inline void tnbLib::PtdModel_BladeExpandedView::SetYb(std::vector<Standard_Real>&& x)
{
	theYb_ = std::move(x);
}
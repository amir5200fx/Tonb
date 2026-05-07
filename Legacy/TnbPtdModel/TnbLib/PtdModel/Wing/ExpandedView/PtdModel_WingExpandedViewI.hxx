#pragma once
inline Standard_Integer
tnbLib::PtdModel_WingExpandedView::NbSpans() const
{
	return (Standard_Integer)theX_.size();
}

inline void tnbLib::PtdModel_WingExpandedView::SetX(std::vector<Standard_Real>&& x)
{
	theX_ = std::move(x);
}

inline void tnbLib::PtdModel_WingExpandedView::SetTf(std::vector<Standard_Real>&& x)
{
	theTf_ = std::move(x);
}

inline void tnbLib::PtdModel_WingExpandedView::SetTb(std::vector<Standard_Real>&& x)
{
	theTb_ = std::move(x);
}

inline void tnbLib::PtdModel_WingExpandedView::SetYf(std::vector<Standard_Real>&& x)
{
	theYf_ = std::move(x);
}

inline void tnbLib::PtdModel_WingExpandedView::SetYb(std::vector<Standard_Real>&& x)
{
	theYb_ = std::move(x);
}
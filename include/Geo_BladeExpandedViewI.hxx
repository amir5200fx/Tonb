#pragma once
inline Standard_Integer
tnbLib::Geo_BladeExpandedView::NbSpans() const
{
	return (Standard_Integer)theX_.size();
}

inline void tnbLib::Geo_BladeExpandedView::SetX(std::vector<Standard_Real>&& x)
{
	theX_ = std::move(x);
}

inline void tnbLib::Geo_BladeExpandedView::SetXs(std::vector<Standard_Real>&& x)
{
	theXs_ = std::move(x);
}

inline void tnbLib::Geo_BladeExpandedView::SetTf(std::vector<Standard_Real>&& x)
{
	theTf_ = std::move(x);
}

inline void tnbLib::Geo_BladeExpandedView::SetTb(std::vector<Standard_Real>&& x)
{
	theTb_ = std::move(x);
}

inline void tnbLib::Geo_BladeExpandedView::SetYf(std::vector<Standard_Real>&& x)
{
	theYf_ = std::move(x);
}

inline void tnbLib::Geo_BladeExpandedView::SetYb(std::vector<Standard_Real>&& x)
{
	theYb_ = std::move(x);
}
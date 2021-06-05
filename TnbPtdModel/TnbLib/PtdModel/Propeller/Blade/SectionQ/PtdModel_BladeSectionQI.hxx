#pragma once
inline void tnbLib::PtdModel_BladeSectionQ::SetBack(const std::vector<Pnt2d>& pts)
{
	theBack_ = pts;
}

inline void tnbLib::PtdModel_BladeSectionQ::SetBack(std::vector<Pnt2d>&& pts)
{
	theBack_ = std::move(pts);
}

inline void tnbLib::PtdModel_BladeSectionQ::SetFace(const std::vector<Pnt2d>& pts)
{
	theFace_ = pts;
}

inline void tnbLib::PtdModel_BladeSectionQ::SetFace(std::vector<Pnt2d>&& pts)
{
	theBack_ = std::move(pts);
}
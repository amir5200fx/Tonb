#pragma once
inline Standard_Integer 
tnbLib::PtdModel_BladeSection::NbSpans() const
{
	return (Standard_Integer)theFace_.size();
}

inline void tnbLib::PtdModel_BladeSection::SetFace(std::vector<Pnt3d>&& pts)
{
	theFace_ = std::move(pts);
}

inline void tnbLib::PtdModel_BladeSection::SetBack(std::vector<Pnt3d>&& pts)
{
	theBack_ = std::move(pts);
}
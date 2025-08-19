#pragma once
inline Standard_Integer 
tnbLib::PtdModel_BladeSection::NbSpans() const
{
	return (Standard_Integer)Face().size();
}

inline void tnbLib::PtdModel_BladeSection::SetFace(std::vector<Pnt3d>&& pts)
{
	base::faceQ f(std::move(pts));
	base::SetQ(std::move(f));
}

inline void tnbLib::PtdModel_BladeSection::SetBack(std::vector<Pnt3d>&& pts)
{
	base::backQ f(std::move(pts));
	base::SetQ(std::move(f));
}
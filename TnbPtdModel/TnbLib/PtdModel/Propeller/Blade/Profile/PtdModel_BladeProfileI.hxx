#pragma once
inline void tnbLib::PtdModel_BladeProfile::SetGeometry(const Handle(Geom2d_Curve)& c)
{
	theGeometry_ = c;
}

inline void tnbLib::PtdModel_BladeProfile::SetGeometry(Handle(Geom2d_Curve) && c)
{
	theGeometry_ = std::move(c);
}
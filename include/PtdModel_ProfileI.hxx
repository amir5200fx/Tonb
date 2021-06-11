#pragma once
inline void tnbLib::PtdModel_Profile::SetGeometry(const Handle(Geom2d_Curve)& c)
{
	theGeometry_ = c;
}

inline void tnbLib::PtdModel_Profile::SetGeometry(Handle(Geom2d_Curve) && c)
{
	theGeometry_ = std::move(c);
}
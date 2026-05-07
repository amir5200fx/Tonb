#pragma once
inline 
void tnbLib::PtdModel_SectionCurve::SetGeometry(const Handle(Geom2d_Curve)& theGeometry)
{
	theGeometry_ = theGeometry;
}

inline 
void tnbLib::PtdModel_SectionCurve::SetGeometry(Handle(Geom2d_Curve)&& theGeometry)
{
	theGeometry_ = std::move(theGeometry);
}
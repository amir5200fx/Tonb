#pragma once
inline void tnbLib::PtdModel_Profile::SetGeometry(const Handle(Geom2d_Curve)& c)
{
	theGeometry_ = c;
}

inline void tnbLib::PtdModel_Profile::SetGeometry(Handle(Geom2d_Curve) && c)
{
	theGeometry_ = std::move(c);
}

inline void tnbLib::PtdModel_Profile::SetTrsf(const std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>& theTrsf)
{
	theTrsf_ = theTrsf;
}

inline void tnbLib::PtdModel_Profile::SetTrsf(std::shared_ptr<GeoLib::AffineTrsf_PtsToUnitSqObj>&& theTrsf)
{
	theTrsf_ = std::move(theTrsf);
}
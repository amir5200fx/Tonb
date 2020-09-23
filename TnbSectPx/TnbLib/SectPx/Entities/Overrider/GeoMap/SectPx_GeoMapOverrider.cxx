#include <SectPx_GeoMapOverrider.hxx>

#include <SectPx_GeoMap.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_GeoMapOverrider::typeName_("geoMap overrider");

tnbLib::word 
tnbLib::SectPx_GeoMapOverrider::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d 
tnbLib::SectPx_GeoMapOverrider::CalcCoord() const
{
	Debug_Null_Pointer(GeoMap());
	auto pnt = GeoMap()->CalcCoord();
	return std::move(pnt);
}
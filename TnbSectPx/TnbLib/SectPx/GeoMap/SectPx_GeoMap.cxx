#include <SectPx_GeoMap.hxx>

Standard_Boolean
tnbLib::SectPx_GeoMap::IsGeoMap() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_GeoMap::RegObjType() const
{
	return sectPxLib::regObjType::geoMap;
}
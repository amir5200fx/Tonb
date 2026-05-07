#include <SectPx_CoordAdaptor.hxx>

#include <SectPx_GeoMap.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_CoordAdaptor)
{
	ar & theGeoMaps_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_CoordAdaptor)
{
	ar & theGeoMaps_;
}
#include <SectPx_GeoMapOverrider.hxx>

#include <SectPx_GeoMap.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_GeoMapOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theGeoMap_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_GeoMapOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theGeoMap_;
}
#include <SectPx_GeoMapOverrider.hxx>

#include <SectPx_GeoMap.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_GeoMapOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theGeoMap_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_GeoMapOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theGeoMap_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_GeoMapOverrider);
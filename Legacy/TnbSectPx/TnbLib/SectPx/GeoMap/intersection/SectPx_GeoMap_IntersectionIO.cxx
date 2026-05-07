#include <SectPx_GeoMap_Intersection.hxx>

#include <SectPx_Coord.hxx>
#include <SectPx_Par.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::GeoMap_Intersection)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);

	ar & theQ0_;
	ar & theQ1_;
	ar & theDir0_;
	ar & theDir1_;
	ar & theAngle0_;
	ar & theAngle1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::GeoMap_Intersection)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);

	ar & theQ0_;
	ar & theQ1_;
	ar & theDir0_;
	ar & theDir1_;
	ar & theAngle0_;
	ar & theAngle1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::GeoMap_Intersection);
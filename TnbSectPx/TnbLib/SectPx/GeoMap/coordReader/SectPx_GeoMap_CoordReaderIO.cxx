#include <SectPx_GeoMap_CoordReader.hxx>

#include <SectPx_Coord.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::GeoMap_CoordReader)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);
	ar & theCoord_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::GeoMap_CoordReader)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);
	ar & theCoord_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::GeoMap_CoordReader);
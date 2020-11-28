#include <SectPx_Datum_GeoField.hxx>

#include <SectPx_GeoMap.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Datum_GeoField)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theMap_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Datum_GeoField)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theMap_;
}
#include <SectPx_Datum_GeoField.hxx>

#include <SectPx_GeoMap.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Datum_GeoField)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theMap_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Datum_GeoField)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theMap_;
}
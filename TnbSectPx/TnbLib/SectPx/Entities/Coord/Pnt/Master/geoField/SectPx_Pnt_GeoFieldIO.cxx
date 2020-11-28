#include <SectPx_Pnt_GeoField.hxx>

#include <SectPx_GeoMap.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_GeoField)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theMap_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_GeoField)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theMap_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_GeoField>);
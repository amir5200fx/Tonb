#include <SectPx_Pnt_GeoField.hxx>

#include <SectPx_GeoMap.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pnt_GeoField)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theMap_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pnt_GeoField)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theMap_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_GeoField>);
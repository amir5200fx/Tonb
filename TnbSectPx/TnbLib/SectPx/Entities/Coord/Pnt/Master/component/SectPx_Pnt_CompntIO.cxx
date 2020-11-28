#include <SectPx_Pnt_Compnt.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_Compnt)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theX_;
	ar & theY_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_Compnt)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theX_;
	ar & theY_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_Compnt>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Compnt>);
#include <SectPx_Pnt_Compnt.hxx>

#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pnt_Compnt)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theX_;
	ar & theY_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pnt_Compnt)
{
	ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
	ar & theX_;
	ar & theY_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_Compnt>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Compnt>);
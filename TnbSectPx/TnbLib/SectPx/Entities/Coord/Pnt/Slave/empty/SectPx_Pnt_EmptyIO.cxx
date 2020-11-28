#include <SectPx_Pnt_Empty.hxx>

#include <SectPx_MasterPnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_Empty)
{
	ar & boost::serialization::base_object<SectPx_SlavePnt>(*this);
	ar & theMaster_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pnt_Empty)
{
	ar & boost::serialization::base_object<SectPx_SlavePnt>(*this);
	ar & theMaster_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Empty>);
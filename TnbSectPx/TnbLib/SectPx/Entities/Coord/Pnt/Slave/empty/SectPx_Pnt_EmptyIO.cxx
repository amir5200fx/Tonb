#include <SectPx_Pnt_Empty.hxx>

#include <SectPx_MasterPnt.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pnt_Empty)
{
	ar & boost::serialization::base_object<SectPx_SlavePnt>(*this);
	ar & theMaster_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pnt_Empty)
{
	ar & boost::serialization::base_object<SectPx_SlavePnt>(*this);
	ar & theMaster_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Empty>);
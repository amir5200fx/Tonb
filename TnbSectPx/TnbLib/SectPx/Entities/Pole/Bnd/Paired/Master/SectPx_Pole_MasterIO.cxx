#include <SectPx_Pole_Master.hxx>

#include <SectPx_Pnt_Compnt.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pole_Master)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pole_Master)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Master);
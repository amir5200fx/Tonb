#include <SectPx_Pole_Master.hxx>

#include <SectPx_Pnt_Compnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Master)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Master)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Master);
#include <SectPx_Pole_Slave.hxx>

#include <SectPx_Pole_Master.hxx>
#include <SectPx_Pnts.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Slave)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & theMaster_;
	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Slave)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & theMaster_;
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Slave);
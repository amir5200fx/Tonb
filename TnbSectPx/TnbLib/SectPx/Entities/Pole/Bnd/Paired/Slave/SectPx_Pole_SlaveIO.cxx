#include <SectPx_Pole_Slave.hxx>

#include <SectPx_Pole_Master.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pole_Slave)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & theMaster_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pole_Slave)
{
	ar & boost::serialization::base_object<SectPx_PairedPole>(*this);
	ar & theMaster_;
}
#include <SectPx_Pole_Dangle.hxx>

#include <SectPx_Pnt_Compnt.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pole_Dangle)
{
	ar & boost::serialization::base_object<SectPx_BndPole>(*this);
	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pole_Dangle)
{
	ar & boost::serialization::base_object<SectPx_BndPole>(*this);
	ar & thePnt_;
}
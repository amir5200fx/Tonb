#include <SectPx_Pole_Corner.hxx>

#include <SectPx_Pnt.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pole_Corner)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pole_Corner)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & thePnt_;
}
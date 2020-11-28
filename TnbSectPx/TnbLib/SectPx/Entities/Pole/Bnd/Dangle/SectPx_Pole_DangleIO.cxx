#include <SectPx_Pole_Dangle.hxx>

#include <SectPx_Pnt_Compnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Dangle)
{
	ar & boost::serialization::base_object<SectPx_BndPole>(*this);
	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Dangle)
{
	ar & boost::serialization::base_object<SectPx_BndPole>(*this);
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Dangle);
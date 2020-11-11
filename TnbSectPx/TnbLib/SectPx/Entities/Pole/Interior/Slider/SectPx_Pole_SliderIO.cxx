#include <SectPx_Pole_Slider.hxx>

#include <SectPx_Pnt_GeoField.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Pole_Slider)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Pole_Slider)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Slider);
#include <SectPx_Pole_Corner.hxx>

#include <SectPx_Pnt.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Corner)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & boost::serialization::base_object<SectPx_Pole_CornerAdaptor>(*this);
	ar & thePnt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Pole_Corner)
{
	ar & boost::serialization::base_object<SectPx_InterPole>(*this);
	ar & boost::serialization::base_object<SectPx_Pole_CornerAdaptor>(*this);
	ar & thePnt_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::Pole_Corner);
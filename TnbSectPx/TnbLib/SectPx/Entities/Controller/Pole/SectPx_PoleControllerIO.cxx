#include <SectPx_PoleController.hxx>

#include <SectPx_Pole_Corner.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_PoleController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCorner_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_PoleController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCorner_;
}
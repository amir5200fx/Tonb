#include <SectPx_Pole_CornerAdaptor.hxx>

#include <SectPx_PoleController.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Pole_CornerAdaptor)
{
	ar & theControllers_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Pole_CornerAdaptor)
{
	ar & theControllers_;
}
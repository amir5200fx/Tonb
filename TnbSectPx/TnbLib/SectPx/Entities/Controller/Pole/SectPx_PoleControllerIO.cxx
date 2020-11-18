#include <SectPx_PoleController.hxx>

#include <SectPx_Pole.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_PoleController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCorner_;
}
#include <SectPx_TightController.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_TightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theLeft_;
	ar & theRight_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_TightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theLeft_;
	ar & theRight_;
}
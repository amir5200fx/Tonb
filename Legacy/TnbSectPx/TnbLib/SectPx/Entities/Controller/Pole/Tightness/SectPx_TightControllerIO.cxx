#include <SectPx_TightController.hxx>

#include <SectPx_SegmentController.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_TightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theLeft_;
	ar & theRight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_TightController)
{
	ar & boost::serialization::base_object<SectPx_PoleController>(*this);
	ar & theLeft_;
	ar & theRight_;
}
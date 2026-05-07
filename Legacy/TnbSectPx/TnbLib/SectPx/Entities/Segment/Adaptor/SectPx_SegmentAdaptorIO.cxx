#include <SectPx_SegmentAdaptor.hxx>

#include <SectPx_SegmentController.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_SegmentAdaptor)
{
	ar & theController_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_SegmentAdaptor)
{
	ar & theController_;
}
#include <SectPx_SegmentController.hxx>

#include <SectPx_CPtsMap.hxx>
#include <SectPx_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_SegmentController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCPts_;
	ar & theSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_SegmentController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCPts_;
	ar & theSegment_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_SegmentController);
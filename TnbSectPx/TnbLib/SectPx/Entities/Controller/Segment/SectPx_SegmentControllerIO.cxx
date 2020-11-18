#include <SectPx_SegmentController.hxx>

#include <SectPx_CPtsMap.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_SegmentController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCPts_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_SegmentController)
{
	ar & boost::serialization::base_object<SectPx_Controller>(*this);
	ar & theCPts_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_SegmentController);
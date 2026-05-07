#include <Aft2d_IterOptNodeSurfaceUniMetric_Calculator.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_IterOptNodeSurfaceUniMetric_Calculator)
{
	ar & boost::serialization::base_object<Aft2d_OptNodeSurfaceUniMetric_Calculator>(*this);
	ar & theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_IterOptNodeSurfaceUniMetric_Calculator)
{
	ar & boost::serialization::base_object<Aft2d_OptNodeSurfaceUniMetric_Calculator>(*this);
	ar & theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_IterOptNodeSurfaceUniMetric_Calculator);
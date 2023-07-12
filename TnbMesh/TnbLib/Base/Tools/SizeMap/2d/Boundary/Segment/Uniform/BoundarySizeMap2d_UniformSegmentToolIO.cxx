#include <BoundarySizeMap2d_UniformSegmentTool.hxx>

#include <Geo_BasicApprxCurve_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_UniformSegmentTool)
{
	ar& boost::serialization::base_object<BoundarySizeMap2d_SegmentTool>(*this);
	ar& theInfo_;

	ar& theUnBalancing_;
	ar& theBucketSize_;
	ar& PostBalance_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_UniformSegmentTool)
{
	ar& boost::serialization::base_object<BoundarySizeMap2d_SegmentTool>(*this);
	ar& theInfo_;

	ar& theUnBalancing_;
	ar& theBucketSize_;
	ar& PostBalance_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::BoundarySizeMap2d_UniformSegmentTool);
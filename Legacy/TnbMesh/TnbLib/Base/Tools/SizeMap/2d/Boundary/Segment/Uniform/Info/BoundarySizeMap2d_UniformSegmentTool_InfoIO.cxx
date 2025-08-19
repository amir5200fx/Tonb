#include <BoundarySizeMap2d_UniformSegmentTool_Info.hxx>

#include <Geo_BasicApprxCurve_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info)
{
	ar& theInfo_;
	ar& theUnBalancing_;
	ar& theBucketSize_;
	ar& PostBalance_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info)
{
	ar& theInfo_;
	ar& theUnBalancing_;
	ar& theBucketSize_;
	ar& PostBalance_;
}
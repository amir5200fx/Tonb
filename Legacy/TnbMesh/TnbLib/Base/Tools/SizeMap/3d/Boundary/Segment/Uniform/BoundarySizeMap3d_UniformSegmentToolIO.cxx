#include <BoundarySizeMap3d_UniformSegmentTool.hxx>

#include <Geo_BasicApprxCurve_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformSegmentTool)
{
	ar & boost::serialization::base_object<BoundarySizeMap3d_SegmentTool>(*this);
	ar & theInfo_;

	ar & theUnBalancing_;
	ar & theBucketSize_;
	ar & PostBalance_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformSegmentTool)
{
	ar & boost::serialization::base_object<BoundarySizeMap3d_SegmentTool>(*this);
	ar & theInfo_;

	ar & theUnBalancing_;
	ar & theBucketSize_;
	ar & PostBalance_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::BoundarySizeMap3d_UniformSegmentTool);
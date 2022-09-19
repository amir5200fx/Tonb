#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>

#include <Geo3d_ApprxSurfPatch_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformFaceTool_Info)
{
	ar & theApprxSurfInfo_;

	ar & theBucketSize_;
	ar & theUnBalancing_;

	ar & PostBalance_;

	ar & theNbSamples_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformFaceTool_Info)
{
	ar & theApprxSurfInfo_;

	ar & theBucketSize_;
	ar & theUnBalancing_;

	ar & PostBalance_;

	ar & theNbSamples_;
}
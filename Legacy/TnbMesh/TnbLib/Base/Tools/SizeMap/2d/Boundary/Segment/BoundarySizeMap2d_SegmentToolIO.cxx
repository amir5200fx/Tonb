#include <BoundarySizeMap2d_SegmentTool.hxx>

#include <Geo2d_SegmentCloud.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_SegmentTool)
{
	ar& boost::serialization::base_object<Mesh2d_BoundarySizeMapTool>(*this);
	ar& theCloud_;
	ar& theMaxNbCorrIters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap2d_SegmentTool)
{
	ar& boost::serialization::base_object<Mesh2d_BoundarySizeMapTool>(*this);
	ar& theCloud_;
	ar& theMaxNbCorrIters_;
}
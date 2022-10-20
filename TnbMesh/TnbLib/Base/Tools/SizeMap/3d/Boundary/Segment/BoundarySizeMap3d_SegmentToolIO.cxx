#include <BoundarySizeMap3d_SegmentTool.hxx>

#include <Geo3d_SegmentCloud.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_SegmentTool)
{
	ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapTool>(*this);
	ar & theCloud_;
	ar & theMaxNbCorrIters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_SegmentTool)
{
	ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapTool>(*this);
	ar & theCloud_;
	ar & theMaxNbCorrIters_;
}
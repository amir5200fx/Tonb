#include <BoundarySizeMap3d_FaceTool.hxx>

#include <Geo3d_PatchCloud.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_FaceTool)
{
	ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapTool>(*this);
	ar & theMaxNbCorrIters_;
	ar & theCloud_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_FaceTool)
{
	ar & boost::serialization::base_object<Mesh3d_BoundarySizeMapTool>(*this);
	ar & theMaxNbCorrIters_;
	ar & theCloud_;
}
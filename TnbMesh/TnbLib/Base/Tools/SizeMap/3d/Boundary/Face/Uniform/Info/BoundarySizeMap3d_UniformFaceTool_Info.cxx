#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>

#include <Geo3d_ApprxSurfPatch_Info.hxx>

Standard_Boolean tnbLib::BoundarySizeMap3d_UniformFaceTool_Info::POST_BALANCE = Standard_True;
Standard_Integer tnbLib::BoundarySizeMap3d_UniformFaceTool_Info::DEFAULT_BUCKET_SIZE = 4;
Standard_Integer tnbLib::BoundarySizeMap3d_UniformFaceTool_Info::DEFAULT_UNBALANCING = 2;

Standard_Integer tnbLib::BoundarySizeMap3d_UniformFaceTool_Info::DEFAULT_NB_SAMPLES = 3;

std::shared_ptr<tnbLib::Geo3d_ApprxSurfPatch_Info> tnbLib::BoundarySizeMap3d_UniformFaceTool_Info::DEFAULT_APPRX_SURF_INFO =
std::make_shared<tnbLib::Geo3d_ApprxSurfPatch_Info>();
#include <Mesh_Values.hxx>

tnbLib::Mesh_Values::Mesh_Values()
	: theBoundaryGrowthRate_(Mesh_VariationRateInfo::moderate)
{
	theSurfaceSize_ = std::make_shared<Mesh_SurfaceSizeValues>();
	theCurvature_ = std::make_shared<Mesh_SurfaceCurvatureValues>();
}
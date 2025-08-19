#include <Mesh_Conditions.hxx>

tnbLib::Mesh_Conditions::Mesh_Conditions()
	: CustomBoundaryGrowthRate_(Standard_False)
	, CustomSurfaceSize_(Standard_False)
	, theCustomSurfaceCurvature_(Mesh_SurfaceCurvatureInfo::continum)
{
	// empty body
}
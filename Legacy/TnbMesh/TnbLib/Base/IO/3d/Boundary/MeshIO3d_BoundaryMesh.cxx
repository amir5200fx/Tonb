#include <MeshIO3d_BoundaryMesh.hxx>

#include <Cad_TModel.hxx>
#include <Entity3d_SurfTriangulation.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MeshIO3d_BoundaryMesh)
{
	ar& theModel_;
	ar& theMeshes_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MeshIO3d_BoundaryMesh)
{
	ar& theModel_;
	ar& theMeshes_;
}
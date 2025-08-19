#include <MeshIO3d_PentaFEA.hxx>

#include <Entity3d_Pentahedralization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MeshIO3d_PentaFEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MeshIO3d_PentaFEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}
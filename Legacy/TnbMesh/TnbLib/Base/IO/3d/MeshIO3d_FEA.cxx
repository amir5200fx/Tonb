#include <MeshIO3d_FEA.hxx>

#include <Entity3d_Tetrahedralization.hxx>

const std::string tnbLib::MeshIO3d_FEA::extension = ".feamsh3d";

TNB_SAVE_IMPLEMENTATION(tnbLib::MeshIO3d_FEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MeshIO3d_FEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}
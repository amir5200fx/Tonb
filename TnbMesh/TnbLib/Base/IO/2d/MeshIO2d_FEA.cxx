#include <MeshIO2d_FEA.hxx>

#include <Entity2d_Triangulation.hxx>

const std::string tnbLib::MeshIO2d_FEA::extension = ".feamsh2d";

TNB_SAVE_IMPLEMENTATION(tnbLib::MeshIO2d_FEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MeshIO2d_FEA)
{
	ar& theMesh_;
	ar& theBoundaries_;
}
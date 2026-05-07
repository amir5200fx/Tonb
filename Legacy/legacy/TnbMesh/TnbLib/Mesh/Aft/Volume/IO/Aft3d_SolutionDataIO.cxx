#include <Aft3d_SolutionData.hxx>

#include <Aft3d_SizeFun.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Tetrahedralization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft3d_SolutionData)
{
	ar& theSurface_;
	ar& theSizeFun_;
	ar& theMesh_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft3d_SolutionData)
{
	ar& theSurface_;
	ar& theSizeFun_;
	ar& theMesh_;
}
#include <Aft3d_SolutionData.hxx>

#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Entity3d_Tetrahedralization.hxx>

const std::string tnbLib::Aft3d_SolutionData::extension = ".aftVolSoluData";

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_SolutionData)
{
	ar& theBndSolu_;
	ar& theMesh_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_SolutionData)
{
	ar& theBndSolu_;
	ar& theMesh_;
}
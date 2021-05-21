#include <HydStatic_SolutionData_Bonjean.hxx>

#include <Marine_Body_Displacer.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Graph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Bonjean)
{
	ar & theBody_;
	ar & theDomain_;

	ar & theGraph_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Bonjean)
{
	ar & theBody_;
	ar & theDomain_;

	ar & theGraph_;
}
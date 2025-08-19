#include <HydStatic_SolutionData_Bonjean2.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Bodies.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Bonjean2)
{
	ar & theDomain_;
	ar & theBody_;

	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Bonjean2)
{
	ar & theDomain_;
	ar & theBody_;

	ar & theSections_;
}
#include <HydStatic_SolutionData_HydCurves.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_Domain.hxx>
#include <HydStatic_HydCurves.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_HydCurves)
{
	ar & theBody_;
	ar & theDomain_;
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_HydCurves)
{
	ar & theBody_;
	ar & theDomain_;
	ar & theCurves_;
}
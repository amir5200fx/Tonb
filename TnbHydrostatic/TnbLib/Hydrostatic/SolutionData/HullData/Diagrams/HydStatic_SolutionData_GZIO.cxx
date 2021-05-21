#include <HydStatic_SolutionData_GZ.hxx>

#include <Marine_Body_Displacer.hxx>
#include <Marine_Domain.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_rArmCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_GZ)
{
	ar & theBody_;
	ar & theDomain_;

	ar & theCrossCurves_;
	ar  &theGz_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_GZ)
{
	ar & theBody_;
	ar & theDomain_;

	ar & theCrossCurves_;
	ar  &theGz_;
}
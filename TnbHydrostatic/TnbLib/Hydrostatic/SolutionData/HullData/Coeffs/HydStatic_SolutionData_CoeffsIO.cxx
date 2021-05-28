#include <HydStatic_SolutionData_Coeffs.hxx>

#include <Marine_Body_Displacer.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Water.hxx>
#include <Marine_Wave.hxx>
#include <HydStatic_FloatBody.hxx>
#include <HydStatic_FormDims.hxx>
#include <HydStatic_FormCoeff.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Coeffs)
{
	ar & IsSymmetric_;
	ar & theHull_;
	ar & theDomain_;
	ar & theWave_;

	ar & theDisplacerAnalysis_;
	ar & theWettedAnalysis_;

	ar & theWater_;
	ar & theFloatBody_;

	ar & theCoeffAnalysis_;

	ar & theCurrent_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_Coeffs)
{
	ar & IsSymmetric_;
	ar & theHull_;
	ar & theDomain_;
	ar & theWave_;

	ar & theDisplacerAnalysis_;
	ar & theWettedAnalysis_;

	ar & theWater_;
	ar & theFloatBody_;

	ar & theCoeffAnalysis_;

	ar & theCurrent_;
}
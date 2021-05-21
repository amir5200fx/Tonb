#include <ISC08_SolutionData_Passenger.hxx>

#include <HydStatic_ModelShape.hxx>
#include <Marine_Wave.hxx>
#include <Marine_Water.hxx>
#include <HydStatic_FormDims.hxx>
#include <HydStatic_FloatBody.hxx>
#include <HydStatic_FormCoeff.hxx>
#include <HydStatic_Shapes.hxx>
#include <HydStatic_rArmCurve_Eff.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::isc08Lib::SolutionData_Passenger)
{
	ar & theCoeffAnalysis_;
	ar & theDisplacerAnalysis_;
	ar & theWater_;
	ar & theFloatBody_;
	ar & theGzEff_;
	ar & theHull_;
	ar & theModel_;
	ar & theTanks_;
	ar & theWave_;
	ar & theWettedAnalysis_;

	ar & theCurrent_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::isc08Lib::SolutionData_Passenger)
{
	ar & theCoeffAnalysis_;
	ar & theDisplacerAnalysis_;
	ar & theWater_;
	ar & theFloatBody_;
	ar & theGzEff_;
	ar & theHull_;
	ar & theModel_;
	ar & theTanks_;
	ar & theWave_;
	ar & theWettedAnalysis_;

	ar & theCurrent_;
}
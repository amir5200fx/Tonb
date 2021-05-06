#include <HydStatic_SolutionData_GzEff.hxx>

#include <StbGMaker_Model.hxx>
#include <HydStatic_Shapes.hxx>
#include <HydStatic_FormDims.hxx>
#include <HydStatic_FormCoeff.hxx>
#include <HydStatic_rArmCurve_Eff.hxx>
#include <HydStatic_Model.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_GzEff)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;

	ar & theHull_;
	ar & theTanks_;

	ar & theCode_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_GzEff)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;

	ar & theHull_;
	ar & theTanks_;

	ar & theCode_;
}
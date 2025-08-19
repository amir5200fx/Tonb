#include <HydStatic_SolutionData_DisplAnalysis.hxx>

#include <Marine_Models.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_DisplAnalysis)
{
	ar & theHull_;
	ar & theDispv_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::SolutionData_DisplAnalysis)
{
	ar & theHull_;
	ar & theDispv_;
}
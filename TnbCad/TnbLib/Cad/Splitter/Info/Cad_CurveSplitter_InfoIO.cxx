#include <Cad_CurveSplitter_Info.hxx>

#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_CurveSplitter_Info)
{
	ar & theCorrInfo_;
	ar & theBisectInfo_;
	ar & theNewtonInfo_;

	ar & theOverallLengthIntgInfo_;
	ar & theIterIntgInfo_;

	ar & theMaxLevel_;

	ar & theUnderRelaxation_;

	ar & theIgnorNonConvergency_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_CurveSplitter_Info)
{
	ar & theCorrInfo_;
	ar & theBisectInfo_;
	ar & theNewtonInfo_;

	ar & theOverallLengthIntgInfo_;
	ar & theIterIntgInfo_;

	ar & theMaxLevel_;

	ar & theUnderRelaxation_;

	ar & theIgnorNonConvergency_;
}
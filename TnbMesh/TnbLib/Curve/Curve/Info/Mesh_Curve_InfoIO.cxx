#include <Mesh_Curve_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_Curve_Info)
{
	ar & theLengthCalcMaxLevel_;
	ar & theUnderRelaxation_;
	
	ar & IgnoreNonConvergency_;

	ar & theOverallLengthIntgInfo_;
	ar & theNewtonIntgInfo_;

	ar & theNewtonIterInfo_;

	ar & theCorrAlgInfo_;
	ar & theBisectInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_Curve_Info)
{
	ar & theLengthCalcMaxLevel_;
	ar & theUnderRelaxation_;

	ar & IgnoreNonConvergency_;

	ar & theOverallLengthIntgInfo_;
	ar & theNewtonIntgInfo_;

	ar & theNewtonIterInfo_;

	ar & theCorrAlgInfo_;
	ar & theBisectInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh_Curve_Info);
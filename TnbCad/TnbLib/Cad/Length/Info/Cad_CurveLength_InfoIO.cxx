#include <Cad_CurveLength_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_CurveLength_Info)
{
	ar & theIntegInfo_;
	ar & theMaxLevel_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_CurveLength_Info)
{
	ar & theIntegInfo_;
	ar & theMaxLevel_;
}
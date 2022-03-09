#include <Aft2d_OptNodeAnIso_nonIterAdaptiveInfo.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_OptNodeAnIso_nonIterAdaptiveInfo)
{
	ar & theCalculatorInfo_;
	ar & theCorrectorInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_OptNodeAnIso_nonIterAdaptiveInfo)
{
	ar & theCalculatorInfo_;
	ar & theCorrectorInfo_;
}
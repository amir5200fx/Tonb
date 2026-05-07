#include <Aft2d_OptNodeAnIso_nonIterAdaptiveInfo.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>

const std::string tnbLib::Aft2d_OptNodeAnIso_nonIterAdaptiveInfo::extension = ".aftOptNodeAnIsoNonIterAdapt";

const std::shared_ptr<tnbLib::Aft_SizeCorr_IterativeInfo> tnbLib::Aft2d_OptNodeAnIso_nonIterAdaptiveInfo::DEFAULT_CALCULATOR_INFO =
std::make_shared<tnbLib::Aft_SizeCorr_IterativeInfo>();

const std::shared_ptr<tnbLib::Aft_SizeCorr_FractionInfo> tnbLib::Aft2d_OptNodeAnIso_nonIterAdaptiveInfo::DEFAULT_CORRECTOR_INFO =
std::make_shared<tnbLib::Aft_SizeCorr_FractionInfo>();
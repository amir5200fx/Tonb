#include <Aft_SizeCorr_IterativeInfo.hxx>

const std::string tnbLib::Aft_SizeCorr_IterativeInfo::extension = ".aftSizeCorrIterInfo";

namespace tnbLib
{
	const Standard_Integer Aft_SizeCorr_IterativeInfo::DEFAULT_MAX_NB_ITERATIONS(50);

	const Standard_Real Aft_SizeCorr_IterativeInfo::DEFAULT_TOLERANCE(0.01);
	const Standard_Real Aft_SizeCorr_IterativeInfo::DEFAULT_UNDER_RELAXATION(0.9);
}
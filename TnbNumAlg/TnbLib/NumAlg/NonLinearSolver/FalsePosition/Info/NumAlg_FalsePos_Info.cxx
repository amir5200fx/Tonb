#include <NumAlg_FalsePos_Info.hxx>

tnbLib::NumAlg_FalsePos_Info::NumAlg_FalsePos_Info()
	: theMaxIterations_(MAX_NB_ITERATIONS)
	, theIter_(0)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theDelta_(DEFAULT_DELTA)
	, theResidual_(0)
	, theResult_(0)
	, IsConverged_(Standard_False)
	, theX0_(0)
	, theX1_(0)
{
	// empty body
}

namespace tnbLib
{
	const Standard_Integer NumAlg_FalsePos_Info::MAX_NB_ITERATIONS(500);

	const Standard_Real NumAlg_FalsePos_Info::DEFAULT_TOLERANCE(1.0E-8);
	const Standard_Real NumAlg_FalsePos_Info::DEFAULT_DELTA(1.0E-6);
}
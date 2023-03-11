#include <NumAlg_AdaptiveInteg_Info.hxx>

const std::string tnbLib::NumAlg_AdaptiveInteg_Info::extension = ".adaptIntegInfo";

tnbLib::NumAlg_AdaptiveInteg_Info::NumAlg_AdaptiveInteg_Info()
	: IsConverged_(Standard_False)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theMaxNbIterations_(DEFAULT_MAX_ITERATIONS)
	, theNbInitIterations_(DEFAULT_INIT_ITERATIONS)
	, theResult_(0)
{}

const Standard_Integer tnbLib::NumAlg_AdaptiveInteg_Info::DEFAULT_INIT_ITERATIONS(0);
const Standard_Integer tnbLib::NumAlg_AdaptiveInteg_Info::DEFAULT_MAX_ITERATIONS(500);

const Standard_Real tnbLib::NumAlg_AdaptiveInteg_Info::DEFAULT_TOLERANCE(1.0E-8);
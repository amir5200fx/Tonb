#include <NumAlg_NewtonSolver_Info.hxx>

#include <Standard_Real.hxx>

tnbLib::NumAlg_NewtonSolver_Info::NumAlg_NewtonSolver_Info()
	: theMaxIterations_(MAX_NB_ITERATIONS)
	, theIter_(0)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
	, theResidual_(0)
	, theResult_(0)
	, theSmall_(DEFAULT_SMALL)
	, theZero_(DEFAULT_ZERO)
	, IsConverged_(Standard_False)
{}

namespace tnbLib
{
	const Standard_Integer NumAlg_NewtonSolver_Info::MAX_NB_ITERATIONS(500);

	const Standard_Real NumAlg_NewtonSolver_Info::DEFAULT_UNDER_RELAXATION(0.9);
	const Standard_Real NumAlg_NewtonSolver_Info::DEFAULT_TOLERANCE(1.0E-8);
	const Standard_Real NumAlg_NewtonSolver_Info::DEFAULT_ZERO((Standard_Real)1.0E-8);
	const Standard_Real NumAlg_NewtonSolver_Info::DEFAULT_SMALL((Standard_Real)1.0E-6);
}
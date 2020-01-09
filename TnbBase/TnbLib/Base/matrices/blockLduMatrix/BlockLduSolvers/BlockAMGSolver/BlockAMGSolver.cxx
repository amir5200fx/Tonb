#include <BlockAMGSolver.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockAMGSolver<Type>::BlockAMGSolver
(
	const word& fieldName,
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
	:
	BlockIterativeSolver<Type>
	(
		fieldName,
		matrix,
		dict
		),
	amg_
	(
		matrix,
		dict
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
typename tnbLib::BlockSolverPerformance<Type>
tnbLib::BlockAMGSolver<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& b
)
{
	// Prepare solver performance
	BlockSolverPerformance<Type> solverPerf
	(
		typeName,
		this->fieldName()
	);

	scalar norm = this->normFactor(x, b);

	// Calculate initial residual
	solverPerf.initialResidual() = gSum(cmptMag(amg_.residual(x, b))) / norm;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// Stop solver on divergence
	Type minResidual = solverPerf.initialResidual();
	scalar divergenceThreshold = 2;

	if (!this->stop(solverPerf))
	{
		do
		{
			amg_.cycle(x, b);

			solverPerf.finalResidual() =
				gSum(cmptMag(amg_.residual(x, b))) / norm;

			solverPerf.nIterations()++;

			// Divergence check
			if
				(
					cmptMax
					(
						solverPerf.finalResidual()
						- divergenceThreshold * minResidual
					) > 0
					&& solverPerf.nIterations() > 5
					)
			{
				break;
			}

			minResidual = tnbLib::min(minResidual, solverPerf.finalResidual());

		} while (!this->stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
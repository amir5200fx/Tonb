#include <BlockGaussSeidelSolver.hxx>


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from matrix and solver data stream
template<class Type>
tnbLib::BlockGaussSeidelSolver<Type>::BlockGaussSeidelSolver
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
	gs_(matrix),
	nSweeps_(readLabel(this->dict().lookup("nSweeps")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
typename tnbLib::BlockSolverPerformance<Type>
tnbLib::BlockGaussSeidelSolver<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& b
)
{
	// Create local references to avoid the spread this-> ugliness
	const BlockLduMatrix<Type>& matrix = this->matrix_;

	// Prepare solver performance
	BlockSolverPerformance<Type> solverPerf
	(
		typeName,
		this->fieldName()
	);

	scalar norm = this->normFactor(x, b);

	Field<Type> wA(x.size());

	// Calculate residual.  Note: sign of residual swapped for efficiency
	matrix.Amul(wA, x);
	wA -= b;

	solverPerf.initialResidual() = gSum(cmptMag(wA)) / norm;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// Check convergence, solve if not converged

	if (!this->stop(solverPerf))
	{
		// Iteration loop

		do
		{
			for (label i = 0; i < nSweeps_; i++)
			{
				gs_.precondition(x, b);

				solverPerf.nIterations()++;
			}

			// Re-calculate residual.  Note: sign of residual swapped
			// for efficiency
			matrix.Amul(wA, x);
			wA -= b;

			solverPerf.finalResidual() = gSum(cmptMag(wA)) / norm;
		} while (!this->stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
#include <BlockCGSolver.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from matrix and solver data stream
template<class Type>
tnbLib::BlockCGSolver<Type>::BlockCGSolver
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
	preconPtr_
	(
		BlockLduPrecon<Type>::New
		(
			matrix,
			this->dict()
		)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
typename tnbLib::BlockSolverPerformance<Type> tnbLib::BlockCGSolver<Type>::solve
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

	// Multiplication helper
	typename BlockCoeff<Type>::multiply mult;

	Field<Type> wA(x.size());

	// Calculate initial residual
	matrix.Amul(wA, x);
	Field<Type> rA(b - wA);

	solverPerf.initialResidual() = gSum(cmptMag(rA)) / norm;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// Check convergence, solve if not converged

	if (!this->stop(solverPerf))
	{
		scalar rho = this->great_;
		scalar rhoOld = rho;

		scalar alpha, beta, wApA;

		Field<Type> pA(x.size());

		do
		{
			rhoOld = rho;

			// Execute preconditioning
			preconPtr_->precondition(wA, rA);

			// Update search directions
			rho = gSumProd(wA, rA);

			beta = rho / rhoOld;

			forAll(pA, i)
			{
				pA[i] = wA[i] + beta * pA[i];
			}

			// Update preconditioner residual
			matrix.Amul(wA, pA);

			wApA = gSumProd(wA, pA);

			// Check for singularity
			if (solverPerf.checkSingularity(mag(wApA) / norm))
			{
				break;
			}

			// Update solution and raw residual
			alpha = rho / wApA;

			forAll(x, i)
			{
				x[i] += alpha * pA[i];
			}

			forAll(rA, i)
			{
				rA[i] -= alpha * wA[i];
			}

			solverPerf.finalResidual() = gSum(cmptMag(rA)) / norm;
			solverPerf.nIterations()++;
		} while (!this->stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
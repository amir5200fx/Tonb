#include <PCG.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(PCG, 0);

	lduSolver::addsymMatrixConstructorToTable<PCG>
		addPCGSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::PCG::PCG
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	lduSolver
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		dict
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::lduSolverPerformance tnbLib::PCG::solve
(
	scalarField& x,
	const scalarField& b,
	const direction cmpt
) const
{
	// --- Setup class containing solver performance data
	lduSolverPerformance solverPerf(typeName, fieldName());

	register label nCells = x.size();

	scalar* __restrict xPtr = x.begin();

	scalarField pA(nCells);
	scalar* __restrict pAPtr = pA.begin();

	scalarField wA(nCells);
	scalar* __restrict wAPtr = wA.begin();

	// Calculate A.x
	matrix_.Amul(wA, x, coupleBouCoeffs_, interfaces_, cmpt);

	// Calculate initial residual field
	scalarField rA(b - wA);
	scalar* __restrict rAPtr = rA.begin();

	// Calculate normalisation factor
	scalar normFactor = this->normFactor(x, b, wA, pA, cmpt);

	if (lduMatrix::debug >= 2)
	{
		Info << "   Normalisation factor = " << normFactor << endl;
	}

	// Calculate normalised residual norm
	solverPerf.initialResidual() = gSumMag(rA) / normFactor;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// Check convergence, solve if not converged
	if (!stop(solverPerf))
	{
		scalar wArA = matrix_.great_;
		scalar wArAold = wArA;

		// Select and construct the preconditioner
		autoPtr<lduPreconditioner> preconPtr;

		preconPtr =
			lduPreconditioner::New
			(
				matrix_,
				coupleBouCoeffs_,
				coupleIntCoeffs_,
				interfaces_,
				dict()
			);

		// Rename the solver pefformance to include precon name
		solverPerf.solverName() = preconPtr->type() + typeName;

		// Solver iteration
		do
		{
			// Store previous wArA
			wArAold = wArA;

			// Precondition residual
			preconPtr->precondition(wA, rA, cmpt);

			// Update search directions:
			wArA = gSumProd(wA, rA);

			if (solverPerf.nIterations() == 0)
			{
				for (register label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell];
				}
			}
			else
			{
				scalar beta = wArA / wArAold;

				for (register label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell] + beta * pAPtr[cell];
				}
			}


			// Update preconditioned residual
			matrix_.Amul(wA, pA, coupleBouCoeffs_, interfaces_, cmpt);

			scalar wApA = gSumProd(wA, pA);


			// Test for singularity
			if (solverPerf.checkSingularity(mag(wApA) / normFactor)) break;


			// Update solution and residual:

			scalar alpha = wArA / wApA;

			for (register label cell = 0; cell < nCells; cell++)
			{
				xPtr[cell] += alpha * pAPtr[cell];
				rAPtr[cell] -= alpha * wAPtr[cell];
			}

			solverPerf.finalResidual() = gSumMag(rA) / normFactor;
			solverPerf.nIterations()++;
		} while (!stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
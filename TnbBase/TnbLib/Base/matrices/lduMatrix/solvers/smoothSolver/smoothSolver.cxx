#include <smoothSolver.hxx>

#include <profiling.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(smoothSolver, 0);

	lduSolver::addsymMatrixConstructorToTable<smoothSolver>
		addsmoothSolverSymMatrixConstructorToTable_;

	lduSolver::addasymMatrixConstructorToTable<smoothSolver>
		addsmoothSolverAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::smoothSolver::smoothSolver
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
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::smoothSolver::readControls()
{
	lduSolver::readControls();
	nSweeps_ = dict().lookupOrDefault<label>("nSweeps", 1);
}


tnbLib::lduSolverPerformance tnbLib::smoothSolver::solve
(
	scalarField& x,
	const scalarField& b,
	const direction cmpt
) const
{
	// Setup class containing solver performance data
	lduSolverPerformance solverPerf(typeName, fieldName());

	// If the nSweeps_ is negative do a fixed number of sweeps
	if (nSweeps_ < 0)
	{
		profilingTrigger smoothProfile("lduMatrix::smoother_" + fieldName());

		autoPtr<lduMatrix::smoother> smootherPtr = lduMatrix::smoother::New
		(
			matrix_,
			coupleBouCoeffs_,
			coupleIntCoeffs_,
			interfaces_,
			dict()
		);

		smootherPtr->smooth
		(
			x,
			b,
			cmpt,
			minIter()
		);

		solverPerf.nIterations() += minIter();
	}

	// HJ, bug fix.  Now do normal sweeps.  HJ, 19/Jan/2009
	scalar normFactor = 0;

	{
		scalarField Ax(x.size());
		scalarField temp(x.size());

		// Calculate A.x
		matrix_.Amul(Ax, x, coupleBouCoeffs_, interfaces_, cmpt);

		// Calculate normalisation factor
		normFactor = this->normFactor(x, b, Ax, temp, cmpt);

		// Calculate residual magnitude
		solverPerf.initialResidual() = gSumMag(b - Ax) / normFactor;
		solverPerf.finalResidual() = solverPerf.initialResidual();
	}

	if (lduMatrix::debug >= 2)
	{
		Info << "   Normalisation factor = " << normFactor << endl;
	}


	// Check convergence, solve if not converged
	if (!stop(solverPerf))
	{
		profilingTrigger smoothProfile("lduMatrix::smoother_" + fieldName());

		autoPtr<lduMatrix::smoother> smootherPtr =
			lduMatrix::smoother::New
			(
				matrix_,
				coupleBouCoeffs_,
				coupleIntCoeffs_,
				interfaces_,
				dict()
			);

		// Smoothing loop
		do
		{
			smootherPtr->smooth
			(
				x,
				b,
				cmpt,
				nSweeps_
			);

			// Calculate the residual to check convergence
			solverPerf.finalResidual() = gSumMag
			(
				matrix_.residual
				(
					x,
					b,
					coupleBouCoeffs_,
					interfaces_,
					cmpt
				)
			) / normFactor;

			solverPerf.nIterations() += nSweeps_;
		} while (!stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
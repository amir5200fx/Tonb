#include <BlockBiCGStabSolver.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from matrix and solver data stream
template<class Type>
tnbLib::BlockBiCGStabSolver<Type>::BlockBiCGStabSolver
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
typename tnbLib::BlockSolverPerformance<Type>
tnbLib::BlockBiCGStabSolver<Type>::solve
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

	Field<Type> p(x.size());

	// Calculate initial residual
	matrix.Amul(p, x);
	Field<Type> r(b - p);

	solverPerf.initialResidual() = gSum(cmptMag(r)) / norm;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// Check convergence, solve if not converged

	if (!this->stop(solverPerf))
	{
		scalar rho = this->great_;
		scalar rhoOld = rho;

		scalar alpha = 0;
		scalar omega = this->great_;
		scalar beta;

		p = pTraits<Type>::zero;
		Field<Type> ph(x.size(), pTraits<Type>::zero);
		Field<Type> v(x.size(), pTraits<Type>::zero);
		Field<Type> s(x.size(), pTraits<Type>::zero);
		Field<Type> sh(x.size(), pTraits<Type>::zero);
		Field<Type> t(x.size(), pTraits<Type>::zero);

		// Calculate transpose residual
		Field<Type> rw(r);

		do
		{
			rhoOld = rho;

			// Update search directions
			rho = gSumProd(rw, r);

			beta = rho / rhoOld * (alpha / omega);

			// Restart if breakdown occurs
			if (rho == 0)
			{
				rw = r;
				rho = gSumProd(rw, r);

				alpha = 0;
				omega = 0;
				beta = 0;
			}

			forAll(p, i)
			{
				p[i] = r[i] + beta * p[i] - beta * omega*v[i];
			}

			preconPtr_->precondition(ph, p);
			matrix.Amul(v, ph);
			alpha = rho / gSumProd(rw, v);

			forAll(s, i)
			{
				s[i] = r[i] - alpha * v[i];
			}

			// Bug fix, Alexander Monakov, 11/Jul/2012
			preconPtr_->precondition(sh, s);
			matrix.Amul(t, sh);
			omega = gSumProd(t, s) / gSumProd(t, t);

			forAll(x, i)
			{
				x[i] = x[i] + alpha * ph[i] + omega * sh[i];
			}

			forAll(r, i)
			{
				r[i] = s[i] - omega * t[i];
			}

			solverPerf.finalResidual() = gSum(cmptMag(r)) / norm;
			solverPerf.nIterations()++;
		} while (!this->stop(solverPerf));
	}

	return solverPerf;
}


// ************************************************************************* //
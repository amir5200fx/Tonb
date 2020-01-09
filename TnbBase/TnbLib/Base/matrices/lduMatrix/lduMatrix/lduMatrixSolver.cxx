#include <lduMatrix.hxx>

#include <diagonalSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(lduSolver, symMatrix);
	defineRunTimeSelectionTable(lduSolver, asymMatrix);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::lduMatrix::solver> tnbLib::lduMatrix::solver::New
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
{
	// Insist of solver name look-up only for complete matrices
	// HJ, 5/Dec/2012

	if (matrix.diagonal())
	{
		return autoPtr<lduSolver>
			(
				new diagonalSolver
				(
					fieldName,
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces,
					dict
				)
				);
	}
	else if (matrix.symmetric())
	{
		word solverName(dict.lookup("solver"));

		symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduSolver::New", dict
			) << "Unknown symmetric matrix solver " << solverName << nl << nl
				<< "Valid symmetric matrix solvers are :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduSolver>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces,
					dict
					)
				);
	}
	else if (matrix.asymmetric())
	{
		word solverName(dict.lookup("solver"));

		asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduSolver::New", dict
			) << "Unknown asymmetric matrix solver " << solverName << nl
				<< "Valid asymmetric matrix solvers are :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduSolver>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces,
					dict
					)
				);
	}
	else
	{
		FatalIOErrorIn
		(
			"lduSolver::New", dict
		) << "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<lduSolver>(NULL);
	}
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

tnbLib::scalar tnbLib::lduMatrix::solver::normFactor
(
	const scalarField& x,
	const scalarField& b,
	const scalarField& Ax,
	scalarField& tmpField,
	const direction cmpt
) const
{
	// Calculate A dot reference value of x
//     matrix_.sumA(tmpField, coupleBouCoeffs_, interfaces_);
//     tmpField *= gAverage(x);

	// Calculate normalisation factor using full multiplication
	// with mean value.  HJ, 5/Nov/2007
	scalarField xRef(x.size(), gAverage(x));

	// Eliminated equations are removed from residual normalisation
	if (!matrix_.eliminatedEqns().empty())
	{
		labelList elim = matrix_.eliminatedEqns().toc();

		forAll(elim, elimI)
		{
			// Set the value of xRef to be identical to the value of x
			// to eliminate the residual
			xRef[elim[elimI]] = x[elim[elimI]];
		}
	}

	matrix_.Amul
	(
		tmpField,
		xRef,
		coupleBouCoeffs_,
		interfaces_,
		cmpt
	);

	return gSum(mag(Ax - tmpField) + mag(b - tmpField)) + matrix_.small_;

	// At convergence this simpler method is equivalent to the above
	// return 2*gSumMag(b) + matrix_.small_;
}


tnbLib::scalar tnbLib::lduMatrix::solver::normFactor
(
	const scalarField& x,
	const scalarField& b,
	const direction cmpt
) const
{
	scalarField wA(x.size());
	scalarField tmpField(x.size());

	matrix_.Amul(wA, x, coupleBouCoeffs_, interfaces_, cmpt);

	return normFactor(x, b, wA, tmpField, cmpt);
}


bool tnbLib::lduMatrix::solver::stop
(
	lduSolverPerformance& solverPerf
) const
{
	if (solverPerf.nIterations() < minIter_)
	{
		return false;
	}

	return converged(solverPerf);
}


bool tnbLib::lduMatrix::solver::converged
(
	lduSolverPerformance& solverPerf
) const
{
	if
		(
			solverPerf.nIterations() >= maxIter_
			|| solverPerf.checkConvergence(tolerance_, relTolerance_)
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::lduMatrix::solver::solver
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	fieldName_(fieldName),
	dict_(dict),
	tolerance_(0),
	relTolerance_(0),
	minIter_(0),
	maxIter_(0),
	matrix_(matrix),
	coupleBouCoeffs_(coupleBouCoeffs),
	coupleIntCoeffs_(coupleIntCoeffs),
	interfaces_(interfaces),
	profile_("lduMatrix::solver_" + fieldName)
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::lduMatrix::solver::readControls()
{
	tolerance_ = dict_.lookupOrDefault<scalar>("tolerance", 1e-6);
	relTolerance_ = dict_.lookupOrDefault<scalar>("relTol", 0);

	minIter_ = dict_.lookupOrDefault<label>("minIter", 0);
	maxIter_ = dict_.lookupOrDefault<label>("maxIter", 1000);
}


void tnbLib::lduMatrix::solver::read(const dictionary& dict)
{
	dict_ = dict;
	readControls();
}


// ************************************************************************* //
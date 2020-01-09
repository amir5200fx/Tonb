#include <fineBlockAMGLevel.hxx>

#include <coarseBlockAMGLevel.hxx>
#include <BlockSolverPerformance.hxx>
#include <BlockCoeffNorm.hxx>
#include <BlockCoeffTwoNorm.hxx>
#include <BlockBiCGStabSolver.hxx>
#include <BlockCGSolver.hxx>
#include <vector2D.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class Type>
tnbLib::fineBlockAMGLevel<Type>::fineBlockAMGLevel
(
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict,
	const word& coarseningType,
	const label groupSize,
	const label minCoarseEqns
)
	:
	matrix_(matrix),
	dict_(dict),
	coarseningPtr_
	(
		BlockMatrixCoarsening<Type>::New
		(
			coarseningType,
			matrix_,
			dict_,
			groupSize,
			minCoarseEqns
		)
	),
	smootherPtr_
	(
		BlockLduSmoother<Type>::New
		(
			matrix,
			dict
			//             ,"fineSmoother"
		)
	),
	Ax_()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Field<Type>& tnbLib::fineBlockAMGLevel<Type>::x()
{
	FatalErrorIn("Field<Type>& tnbLib::fineBlockAMGLevel<Type>::x()")
		<< "x is not available."
		<< abort(FatalError);

	// Dummy return
	return const_cast<Field<Type>&>(Field<Type>::null());
}


template<class Type>
tnbLib::Field<Type>& tnbLib::fineBlockAMGLevel<Type>::b()
{
	FatalErrorIn("Field<Type>& tnbLib::fineBlockAMGLevel<Type>::b()")
		<< "b is not available."
		<< abort(FatalError);

	// Dummy return
	return const_cast<Field<Type>&>(Field<Type>::null());
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::residual
(
	const Field<Type>& x,
	const Field<Type>& b,
	Field<Type>& res
) const
{
	matrix_.Amul
	(
		res,
		x
	);

	// residual = b - Ax
	forAll(b, i)
	{
		res[i] = b[i] - res[i];
	}
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::restrictResidual
(
	const Field<Type>& x,
	const Field<Type>& b,
	Field<Type>& xBuffer,
	Field<Type>& coarseRes,
	bool preSweepsDone
) const
{
	if (preSweepsDone)
	{
		// Calculate residual
		residual(x, b, xBuffer);
	}

	// Here x != 0.  It is assumed that the buffer will contain the residual
	// if no pre-sweeps have been done.  HJ, 4/Sep/2006
	coarseningPtr_->restrictResidual(xBuffer, coarseRes);
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::prolongateCorrection
(
	Field<Type>& x,
	const Field<Type>& coarseX
) const
{
	coarseningPtr_->prolongateCorrection(x, coarseX);
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::smooth
(
	Field<Type>& x,
	const Field<Type>& b,
	const label nSweeps
) const
{
	smootherPtr_->smooth(x, b, nSweeps);
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& b,
	const scalar tolerance,
	const scalar relTol
) const
{
	Info << "Fine level solver" << endl;

	// Create artificial dictionary for finest solution
	dictionary finestDict;
	finestDict.add("minIter", 1);
	finestDict.add("maxIter", 1000);
	finestDict.add("tolerance", tolerance);
	finestDict.add("relTol", relTol);

	if (matrix_.symmetric())
	{
		finestDict.add("preconditioner", "Cholesky");

		BlockSolverPerformance<Type> coarseSolverPerf =
			BlockCGSolver<Type>
			(
				"topLevelCorr",
				matrix_,
				finestDict
				).solve(x, b);
	}
	else
	{
		finestDict.add("preconditioner", "Cholesky");

		BlockSolverPerformance<Type> coarseSolverPerf =
			BlockBiCGStabSolver<Type>
			(
				"topLevelCorr",
				matrix_,
				finestDict
				).solve(x, b);
	}
}


template<class Type>
void tnbLib::fineBlockAMGLevel<Type>::scaleX
(
	Field<Type>& x,
	const Field<Type>& b,
	Field<Type>& xBuffer
) const
{
	// KRJ: 2013-02-05: Removed subfield, creating a new field
	// Initialise and size buffer to avoid multiple allocation.
	// Buffer is created as private data of AMG level
	// HJ, 26/Feb/2015
	if (Ax_.empty())
	{
		Ax_.setSize(x.size());
	}

	matrix_.Amul(Ax_, x);

	// Variant 1: scale complete x with a single scaling factor
	scalar scalingFactorNum = sumProd(x, b);
	scalar scalingFactorDenom = sumProd(x, Ax_);

	vector2D scalingVector(scalingFactorNum, scalingFactorDenom);
	reduce(scalingVector, sumOp<vector2D>());

	// Scale x
	if
		(
			mag(scalingVector[0]) > SMALL
			&& mag(scalingVector[0]) < GREAT
			&& mag(scalingVector[0]) > SMALL
			&& mag(scalingVector[1]) < GREAT
			&& scalingVector[0] * scalingVector[1] > 0
			)
	{
		// Regular scaling
		x *= tnbLib::max
		(
			0.01,
			tnbLib::min
			(
				scalingVector[0] / scalingVector[1],
				100
			)
		);
	}
}


template<class Type>
tnbLib::autoPtr<tnbLib::BlockAMGLevel<Type> >
tnbLib::fineBlockAMGLevel<Type>::makeNextLevel() const
{
	if (coarseningPtr_->coarsen())
	{
		return coarseningPtr_->restrictMatrix();
	}
	else
	{
		// Final level: cannot coarsen
		return autoPtr<tnbLib::BlockAMGLevel<Type> >();
	}
}


// ************************************************************************* //
#include <coarseBlockAMGLevel.hxx>

#include <SubField.hxx>
#include <vector2D.hxx>
#include <coeffFields.hxx>
#include <BlockSolverPerformance.hxx>
#include <BlockGMRESSolver.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class Type>
tnbLib::coarseBlockAMGLevel<Type>::coarseBlockAMGLevel
(
	autoPtr<lduPrimitiveMesh> addrPtr,
	autoPtr<BlockLduMatrix<Type> > matrixPtr,
	const dictionary& dict,
	const word& coarseningType,
	const label groupSize,
	const label minCoarseEqns
)
	:
	addrPtr_(addrPtr),
	matrixPtr_(matrixPtr),
	x_(matrixPtr_->diag().size(), pTraits<Type>::zero),
	b_(matrixPtr_->diag().size(), pTraits<Type>::zero),
	dict_(dict),
	coarseningPtr_
	(
		BlockMatrixCoarsening<Type>::New
		(
			coarseningType,
			matrixPtr_,
			dict_,
			groupSize,
			minCoarseEqns
		)
	),
	smootherPtr_
	(
		BlockLduSmoother<Type>::New
		(
			matrixPtr_,
			dict
			//             ,"coarseSmoother"
		)
	),
	Ax_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::coarseBlockAMGLevel<Type>::~coarseBlockAMGLevel()
{
	// Clear addressing interfaces
	if (addrPtr_.valid())
	{
		addrPtr_().clearInterfaces();
	}

	// Clear matrix interfaces
	if (matrixPtr_.valid())
	{
		matrixPtr_().clearInterfaces();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Field<Type>& tnbLib::coarseBlockAMGLevel<Type>::x()
{
	return x_;
}


template<class Type>
tnbLib::Field<Type>& tnbLib::coarseBlockAMGLevel<Type>::b()
{
	return b_;
}


template<class Type>
void tnbLib::coarseBlockAMGLevel<Type>::residual
(
	const Field<Type>& x,
	const Field<Type>& b,
	Field<Type>& res
) const
{
	// Calculate residual
	matrixPtr_->Amul
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
void tnbLib::coarseBlockAMGLevel<Type>::restrictResidual
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
		// KRJ: 2012-12-14 ::subField removed. Creating buffer locally
		Field<Type> resBuf(x.size());

		Field<Type>& res = reinterpret_cast<Field<Type>&>(resBuf);

		residual(x, b, res);

		coarseningPtr_->restrictResidual(res, coarseRes);
	}
	else
	{
		// No pre-sweeps done: x = 0 and residual = b
		coarseningPtr_->restrictResidual(b, coarseRes);
	}
}


template<class Type>
void tnbLib::coarseBlockAMGLevel<Type>::prolongateCorrection
(
	Field<Type>& x,
	const Field<Type>& coarseX
) const
{
	coarseningPtr_->prolongateCorrection(x, coarseX);
}


template<class Type>
void tnbLib::coarseBlockAMGLevel<Type>::smooth
(
	Field<Type>& x,
	const Field<Type>& b,
	const label nSweeps
) const
{
	smootherPtr_->smooth(x, b, nSweeps);
}


template<class Type>
void tnbLib::coarseBlockAMGLevel<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& b,
	const scalar tolerance,
	const scalar relTol
) const
{
	BlockSolverPerformance<Type> coarseSolverPerf
	(
		BlockGMRESSolver<Type>::typeName,
		"topLevelCorr"
	);

	label maxIter = tnbLib::min(2 * coarseningPtr_->minCoarseEqns(), 100);

	// Create artificial dictionary for top-level solution
	dictionary topLevelDict;
	topLevelDict.add("nDirections", "5");
	topLevelDict.add("minIter", 1);
	topLevelDict.add("maxIter", maxIter);
	topLevelDict.add("tolerance", tolerance);
	topLevelDict.add("relTol", relTol);

	// Avoid issues with round-off on strict tolerance setup
	// HJ, 27/Jun/2013
	// Create multiplication function object
	typename BlockCoeff<Type>::multiply mult;

	CoeffField<Type> invDiag = inv(matrixPtr_->diag());
	multiply(x, invDiag, b);

	// Do not solve if the number of equations is smaller than 5
	if (coarseningPtr_->minCoarseEqns() < 5)
	{
		return;
	}

	// Switch of debug in top-level direct solve
	label oldDebug = BlockLduMatrix<Type>::debug();

	if (BlockLduMatrix<Type>::debug >= 4)
	{
		BlockLduMatrix<Type>::debug = 1;
	}
	else
	{
		BlockLduMatrix<Type>::debug = 0;
	}

	if (matrixPtr_->symmetric())
	{
		topLevelDict.add("preconditioner", "Cholesky");

		coarseSolverPerf =
			//         BlockCGSolver<Type>
			BlockGMRESSolver<Type>
			(
				"topLevelCorr",
				matrixPtr_,
				topLevelDict
				).solve(x, b);
	}
	else
	{
		topLevelDict.add("preconditioner", "Cholesky");

		coarseSolverPerf =
			//         BlockBiCGStabSolver<Type>
			BlockGMRESSolver<Type>
			(
				"topLevelCorr",
				matrixPtr_,
				topLevelDict
				).solve(x, b);
	}

	// Restore debug
	BlockLduMatrix<Type>::debug = oldDebug;

	// Escape cases of top-level solver divergence
	if
		(
			coarseSolverPerf.nIterations() == maxIter
			&& (
				coarseSolverPerf.finalResidual()
				>= coarseSolverPerf.initialResidual()
				)
			)
	{
		// Top-level solution failed.  Attempt rescue
		// HJ, 27/Jul/2013
		multiply(x, invDiag, b);

		// Print top level correction failure as info for user
		coarseSolverPerf.print();
	}

	if (BlockLduMatrix<Type>::debug >= 3)
	{
		coarseSolverPerf.print();
	}
}


template<class Type>
void tnbLib::coarseBlockAMGLevel<Type>::scaleX
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

	matrixPtr_->Amul(Ax_, x);

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
tnbLib::coarseBlockAMGLevel<Type>::makeNextLevel() const
{
	if (coarseningPtr_->coarsen())
	{
		return coarseningPtr_->restrictMatrix();
	}
	else
	{
		// Final level: cannot coarsen
		return autoPtr<BlockAMGLevel<Type> >();
	}
}


// ************************************************************************* //
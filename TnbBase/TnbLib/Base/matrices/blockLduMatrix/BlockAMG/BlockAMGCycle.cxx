#include <BlockAMGCycle.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from AMG level
template<class Type>
tnbLib::BlockAMGCycle<Type>::BlockAMGCycle
(
	autoPtr<BlockAMGLevel<Type> > levelPtr
)
	:
	levelPtr_(levelPtr),
	coarseLevelPtr_(NULL),
	nLevels_(0)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockAMGCycle<Type>::~BlockAMGCycle()
{
	deleteDemandDrivenData(coarseLevelPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockAMGCycle<Type>::makeCoarseLevels(const label nMaxLevels)
{
	// Make coarse levels
	if (nLevels_ == 0)
	{
		bool addCoarse = true;
		BlockAMGCycle<Type>* curCyclePtr = this;

		// Do forever
		for (;;)
		{
			nLevels_++;

			autoPtr<BlockAMGLevel<Type> > coarsePtr =
				curCyclePtr->levelPtr_->makeNextLevel();

			// Check if a coarse level is valid and allowed
			if (nLevels_ >= nMaxLevels || !coarsePtr.valid())
			{
				addCoarse = false;
			}

			reduce(addCoarse, andOp<bool>());

			if (addCoarse)
			{
				curCyclePtr->coarseLevelPtr_ =
					new BlockAMGCycle<Type>(coarsePtr);

				// Point to the next coarse level
				curCyclePtr = curCyclePtr->coarseLevelPtr_;
			}
			else
			{
				break;
			}
		}

		if (BlockLduMatrix<Type>::debug >= 2)
		{
			Info << "Created " << nLevels_ << " AMG levels" << endl;
		}
	}
}


template<class Type>
void tnbLib::BlockAMGCycle<Type>::fixedCycle
(
	Field<Type>& x,
	const Field<Type>& b,
	Field<Type>& xBuffer,
	const blockAMGCycleName::cycleType cycle,
	const label nPreSweeps,
	const label nPostSweeps,
	const bool scale
) const
{
	if (coarseLevelPtr_)
	{
		// Pre-smoothing
		levelPtr_->smooth(x, b, nPreSweeps);

		// Get reference to coarse level
		Field<Type>& xCoarse = coarseLevelPtr_->levelPtr_->x();
		Field<Type>& bCoarse = coarseLevelPtr_->levelPtr_->b();

		// Zero out coarse x
		xCoarse = pTraits<Type>::zero;

		// Restrict residual: optimisation on number of pre-sweeps
		levelPtr_->restrictResidual
		(
			x,
			b,
			xBuffer,
			bCoarse,
			nPreSweeps > 0 || cycle != V_CYCLE
		);

		coarseLevelPtr_->fixedCycle
		(
			xCoarse,
			bCoarse,
			xBuffer,
			cycle,
			nPreSweeps,
			nPostSweeps,
			scale
		);

		if (cycle == F_CYCLE)
		{
			coarseLevelPtr_->fixedCycle
			(
				xCoarse,
				bCoarse,
				xBuffer,
				V_CYCLE,
				nPreSweeps,
				nPostSweeps,
				scale
			);
		}
		else if (cycle == W_CYCLE)
		{
			coarseLevelPtr_->fixedCycle
			(
				xCoarse,
				bCoarse,
				xBuffer,
				W_CYCLE,
				nPreSweeps,
				nPostSweeps,
				scale
			);
		}

		if (scale)
		{
			// Calculate scaling factor using a buffer
			coarseLevelPtr_->levelPtr_->scaleX(xCoarse, bCoarse, xBuffer);
		}

		levelPtr_->prolongateCorrection(x, xCoarse);

		// Post-smoothing
		levelPtr_->smooth(x, b, nPostSweeps);
	}
	else
	{
		// Call direct solver
		levelPtr_->solve(x, b, 1e-9, 0);
	}
}


// ************************************************************************* //
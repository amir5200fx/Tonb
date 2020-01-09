#include <BlockAMGPrecon.hxx>

#include <dictionary.hxx>
#include <fineBlockAMGLevel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockAMGPrecon<Type>::BlockAMGPrecon
(
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
	:
	BlockLduPrecon<Type>
	(
		matrix
		),
	cycle_(BlockAMGCycle<Type>::cycleNames_.read(dict.lookup("cycle"))),
	nPreSweeps_(readLabel(dict.lookup("nPreSweeps"))),
	nPostSweeps_(readLabel(dict.lookup("nPostSweeps"))),
	nMaxLevels_(readLabel(dict.lookup("nMaxLevels"))),
	scale_(dict.lookup("scale")),
	amgPtr_
	(
		new BlockAMGCycle<Type>
		(
			autoPtr<BlockAMGLevel<Type> >
			(
				new fineBlockAMGLevel<Type>
				(
					matrix,
					dict,
					dict.lookup("coarseningType"),
					readLabel(dict.lookup("groupSize")),
					readLabel(dict.lookup("minCoarseEqns"))
					)
				)
			)
	),
	xBuffer_(matrix.lduAddr().size())
{
	// Make coarse levels
	amgPtr_->makeCoarseLevels(nMaxLevels_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockAMGPrecon<Type>::~BlockAMGPrecon()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::label tnbLib::BlockAMGPrecon<Type>::nLevels() const
{
	return amgPtr_->nLevels();
}


template<class Type>
const tnbLib::Field<Type>& tnbLib::BlockAMGPrecon<Type>::residual
(
	const Field<Type>& x,
	const Field<Type>& b
) const
{
	// Calculate residual
	amgPtr_->residual(x, b, xBuffer_);

	return xBuffer_;
}


template<class Type>
void tnbLib::BlockAMGPrecon<Type>::cycle
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	amgPtr_->fixedCycle
	(
		x,
		b,
		xBuffer_,
		cycle_,
		nPreSweeps_,
		nPostSweeps_,
		scale_
	);
}


template<class Type>
void tnbLib::BlockAMGPrecon<Type>::precondition
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	// Execute preconditioning
	residual(x, b);
	cycle(x, b);
}


// ************************************************************************* //
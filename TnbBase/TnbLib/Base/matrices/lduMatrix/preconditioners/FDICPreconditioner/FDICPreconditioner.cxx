#include <FDICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(FDICPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<FDICPreconditioner>
		addFDICPreconditionerSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::FDICPreconditioner::FDICPreconditioner
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary&
)
	:
	lduPreconditioner
	(
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces
	),
	rD_(matrix.diag()),
	rDuUpper_(matrix.upper().size()),
	rDlUpper_(matrix.upper().size())
{
	scalar* __restrict rDPtr = rD_.begin();
	scalar* __restrict rDuUpperPtr = rDuUpper_.begin();
	scalar* __restrict rDlUpperPtr = rDlUpper_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();
	const scalar* const __restrict upperPtr = matrix_.upper().begin();

	register label nCells = rD_.size();
	register label nFaces = matrix_.upper().size();

	for (register label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= sqr(upperPtr[face]) / rDPtr[lPtr[face]];
	}

	// Generate reciprocal FDIC
	for (register label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}

	for (register label face = 0; face < nFaces; face++)
	{
		rDuUpperPtr[face] = rDPtr[uPtr[face]] * upperPtr[face];
		rDlUpperPtr[face] = rDPtr[lPtr[face]] * upperPtr[face];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::FDICPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();
	const scalar* __restrict rDPtr = rD_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();

	const scalar* const __restrict rDuUpperPtr = rDuUpper_.begin();
	const scalar* const __restrict rDlUpperPtr = rDlUpper_.begin();

	register label nCells = wA.size();
	register label nFaces = matrix_.upper().size();
	register label nFacesM1 = nFaces - 1;

	for (register label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}

	for (register label face = 0; face < nFaces; face++)
	{
		wAPtr[uPtr[face]] -= rDuUpperPtr[face] * wAPtr[lPtr[face]];
	}

	for (register label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -= rDlUpperPtr[face] * wAPtr[uPtr[face]];
	}
}


// ************************************************************************* //
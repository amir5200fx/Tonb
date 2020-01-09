#include <DICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DICPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<DICPreconditioner>
		addDICPreconditionerSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DICPreconditioner::calcReciprocalD
(
	scalarField& rD,
	const lduMatrix& matrix
)
{
	scalar* __restrict rDPtr = rD.begin();

	const label* const __restrict uPtr = matrix.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = matrix.lduAddr().lowerAddr().begin();
	const scalar* const __restrict upperPtr = matrix.upper().begin();

	// Calculate the DIC diagonal
	register const label nFaces = matrix.upper().size();
	for (register label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= upperPtr[face] * upperPtr[face] / rDPtr[lPtr[face]];
	}


	// Calculate the reciprocal of the preconditioned diagonal
	register const label nCells = rD.size();

	for (register label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DICPreconditioner::DICPreconditioner
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
	rD_(matrix.diag())
{
	calcReciprocalD(rD_, matrix);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DICPreconditioner::precondition
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
	const scalar* const __restrict upperPtr = matrix_.upper().begin();

	register label nCells = wA.size();
	register label nFaces = matrix_.upper().size();
	register label nFacesM1 = nFaces - 1;

	for (register label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}

	for (register label face = 0; face < nFaces; face++)
	{
		wAPtr[uPtr[face]] -= rDPtr[uPtr[face]] * upperPtr[face] * wAPtr[lPtr[face]];
	}

	for (register label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -= rDPtr[lPtr[face]] * upperPtr[face] * wAPtr[uPtr[face]];
	}
}


// ************************************************************************* //
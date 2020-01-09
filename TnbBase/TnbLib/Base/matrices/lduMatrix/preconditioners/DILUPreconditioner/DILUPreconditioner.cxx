#include <DILUPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DILUPreconditioner, 0);

	lduPreconditioner::
		addsymMatrixConstructorToTable<DILUPreconditioner>
		addDILUPreconditionerSymMatrixConstructorToTable_;

	lduPreconditioner::
		addasymMatrixConstructorToTable<DILUPreconditioner>
		addDILUPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DILUPreconditioner::DILUPreconditioner
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

void tnbLib::DILUPreconditioner::calcReciprocalD
(
	scalarField& rD,
	const lduMatrix& matrix
)
{
	scalar* __restrict rDPtr = rD.begin();

	const label* const __restrict uPtr =
		matrix.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix.lduAddr().lowerAddr().begin();

	const scalar* const __restrict upperPtr = matrix.upper().begin();
	const scalar* const __restrict lowerPtr = matrix.lower().begin();

	register label nFaces = matrix.upper().size();
	for (register label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= upperPtr[face] * lowerPtr[face] / rDPtr[lPtr[face]];
	}


	// Calculate the reciprocal of the preconditioned diagonal
	register label nCells = rD.size();

	for (register label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}
}


void tnbLib::DILUPreconditioner::precondition
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
	const label* const __restrict losortPtr =
		matrix_.lduAddr().losortAddr().begin();

	const scalar* const __restrict upperPtr = matrix_.upper().begin();
	const scalar* const __restrict lowerPtr = matrix_.lower().begin();

	register label nCells = wA.size();
	register label nFaces = matrix_.upper().size();
	register label nFacesM1 = nFaces - 1;

	for (register label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}


	register label sface;

	for (register label face = 0; face < nFaces; face++)
	{
		sface = losortPtr[face];
		wAPtr[uPtr[sface]] -=
			rDPtr[uPtr[sface]] * lowerPtr[sface] * wAPtr[lPtr[sface]];
	}

	for (register label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -=
			rDPtr[lPtr[face]] * upperPtr[face] * wAPtr[uPtr[face]];
	}
}


void tnbLib::DILUPreconditioner::preconditionT
(
	scalarField& wT,
	const scalarField& rT,
	const direction
) const
{
	scalar* __restrict wTPtr = wT.begin();
	const scalar* __restrict rTPtr = rT.begin();
	const scalar* __restrict rDPtr = rD_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();
	const label* const __restrict losortPtr =
		matrix_.lduAddr().losortAddr().begin();

	const scalar* const __restrict upperPtr = matrix_.upper().begin();
	const scalar* const __restrict lowerPtr = matrix_.lower().begin();

	register label nCells = wT.size();
	register label nFaces = matrix_.upper().size();
	register label nFacesM1 = nFaces - 1;

	for (register label cell = 0; cell < nCells; cell++)
	{
		wTPtr[cell] = rDPtr[cell] * rTPtr[cell];
	}

	for (register label face = 0; face < nFaces; face++)
	{
		wTPtr[uPtr[face]] -=
			rDPtr[uPtr[face]] * upperPtr[face] * wTPtr[lPtr[face]];
	}


	register label sface;

	for (register label face = nFacesM1; face >= 0; face--)
	{
		sface = losortPtr[face];
		wTPtr[lPtr[sface]] -=
			rDPtr[lPtr[sface]] * lowerPtr[sface] * wTPtr[uPtr[sface]];
	}
}


// ************************************************************************* //
#include <diagonalPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(diagonalPreconditioner, 0);

	lduPreconditioner::
		addsymMatrixConstructorToTable<diagonalPreconditioner>
		adddiagonalPreconditionerSymMatrixConstructorToTable_;

	lduPreconditioner::
		addasymMatrixConstructorToTable<diagonalPreconditioner>
		adddiagonalPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diagonalPreconditioner::diagonalPreconditioner
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
	rD(matrix.diag().size())
{
	scalar* __restrict rDPtr = rD.begin();
	const scalar* __restrict DPtr = matrix_.diag().begin();

	register label nCells = rD.size();

	// Generate reciprocal diagonal
	for (register label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / DPtr[cell];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::diagonalPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();
	const scalar* __restrict rDPtr = rD.begin();

	register label nCells = wA.size();

	for (register label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}
}


// ************************************************************************* //
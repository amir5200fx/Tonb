#include <noPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(noPreconditioner, 0);

	lduPreconditioner::
		addsymMatrixConstructorToTable<noPreconditioner>
		addnoPreconditionerSymMatrixConstructorToTable_;

	lduPreconditioner::
		addasymMatrixConstructorToTable<noPreconditioner>
		addnoPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noPreconditioner::noPreconditioner
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
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::noPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();

	register label nCells = wA.size();

	for (register label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rAPtr[cell];
	}
}


// ************************************************************************* //
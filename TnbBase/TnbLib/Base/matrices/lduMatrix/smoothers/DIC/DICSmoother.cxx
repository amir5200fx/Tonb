#include <DICSmoother.hxx>

#include <DICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DICSmoother, 0);

	lduSmoother::addsymMatrixConstructorToTable<DICSmoother>
		addDICSmootherSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DICSmoother::DICSmoother
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	lduSmoother
	(
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces
	),
	rD_(matrix_.diag())
{
	DICPreconditioner::calcReciprocalD(rD_, matrix_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DICSmoother::smooth
(
	scalarField& x,
	const scalarField& b,
	const direction cmpt,
	const label nSweeps
) const
{
	const scalar* const __restrict rDPtr = rD_.begin();
	const scalar* const __restrict upperPtr = matrix_.upper().begin();
	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();

	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();

	// Temporary storage for the residual
	scalarField rA(rD_.size());
	scalar* __restrict rAPtr = rA.begin();

	for (label sweep = 0; sweep < nSweeps; sweep++)
	{
		matrix_.residual
		(
			rA,
			x,
			b,
			coupleBouCoeffs_,
			interfaces_,
			cmpt
		);

		rA *= rD_;

		register label nFaces = matrix_.upper().size();
		for (register label face = 0; face < nFaces; face++)
		{
			register label u = uPtr[face];
			rAPtr[u] -= rDPtr[u] * upperPtr[face] * rAPtr[lPtr[face]];
		}

		register label nFacesM1 = nFaces - 1;
		for (register label face = nFacesM1; face >= 0; face--)
		{
			register label l = lPtr[face];
			rAPtr[l] -= rDPtr[l] * upperPtr[face] * rAPtr[uPtr[face]];
		}

		x += rA;
	}
}


// ************************************************************************* //
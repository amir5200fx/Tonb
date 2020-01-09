#include <DICGaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DICGaussSeidelSmoother, 0);

	lduSmoother::addsymMatrixConstructorToTable<DICGaussSeidelSmoother>
		addDICGaussSeidelSmootherSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DICGaussSeidelSmoother::DICGaussSeidelSmoother
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
	dicSmoother_
	(
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces
	),
	gsSmoother_
	(
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DICGaussSeidelSmoother::smooth
(
	scalarField& x,
	const scalarField& b,
	const direction cmpt,
	const label nSweeps
) const
{
	dicSmoother_.smooth(x, b, cmpt, nSweeps);
	gsSmoother_.smooth(x, b, cmpt, nSweeps);
}


// ************************************************************************* //
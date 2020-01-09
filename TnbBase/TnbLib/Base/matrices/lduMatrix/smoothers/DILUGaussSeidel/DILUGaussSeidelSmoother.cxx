#include <DILUGaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DILUGaussSeidelSmoother, 0);

	lduSmoother::
		addasymMatrixConstructorToTable<DILUGaussSeidelSmoother>
		addDILUGaussSeidelSmootherAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DILUGaussSeidelSmoother::DILUGaussSeidelSmoother
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	lduMatrix::smoother
	(
		matrix,
		interfaceBouCoeffs,
		coupleIntCoeffs,
		interfaces
	),
	diluSmoother_
	(
		matrix,
		interfaceBouCoeffs,
		coupleIntCoeffs,
		interfaces
	),
	gsSmoother_
	(
		matrix,
		interfaceBouCoeffs,
		coupleIntCoeffs,
		interfaces
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DILUGaussSeidelSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	diluSmoother_.smooth(psi, source, cmpt, nSweeps);
	gsSmoother_.smooth(psi, source, cmpt, nSweeps);
}


// ************************************************************************* //
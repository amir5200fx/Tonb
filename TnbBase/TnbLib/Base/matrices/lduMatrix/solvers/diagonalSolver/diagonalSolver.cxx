#include <diagonalSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(diagonalSolver, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diagonalSolver::diagonalSolver
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	lduMatrix::solver
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		dict
	)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::lduSolverPerformance tnbLib::diagonalSolver::solve
(
	scalarField& x,
	const scalarField& b,
	const direction cmpt
) const
{
	x = b / matrix_.diag();

	return lduSolverPerformance
	(
		typeName,
		fieldName(),
		0,
		0,
		0,
		true,
		false
	);
}


// ************************************************************************* //
#include <BICCG.hxx>

#include <IStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(BICCG, 0);

	lduSolver::addsymMatrixConstructorToTable<BICCG>
		addBICCGSymMatrixConstructorToTable_;

	lduSolver::addasymMatrixConstructorToTable<BICCG>
		addBICCGAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::dictionary tnbLib::BICCG::solverDict
(
	const scalar tol,
	const scalar relTol
)
{
	dictionary dict(IStringStream("solver PBiCG; preconditioner DILU;")());
	dict.add("tolerance", tol);
	dict.add("relTol", relTol);

	return dict;
}


tnbLib::dictionary tnbLib::BICCG::solverDict
(
	Istream& is
)
{
	scalar tol(readScalar(is));
	scalar relTol(readScalar(is));

	return solverDict(tol, relTol);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BICCG::BICCG
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	PBiCG
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		dict
	)
{}


tnbLib::BICCG::BICCG
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const scalar tolerance,
	const scalar relTol
)
	:
	PBiCG
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		solverDict(tolerance, relTol)
	)
{}

// ************************************************************************* //
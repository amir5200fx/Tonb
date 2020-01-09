#include <ICCG.hxx>

#include <IStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ICCG, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<ICCG>
		addICCGSymMatrixConstructorToTable_;
}

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::dictionary tnbLib::ICCG::solverDict
(
	const scalar tol,
	const scalar relTol
)
{
	dictionary dict(IStringStream("solver PCG; preconditioner DIC;")());
	dict.add("tolerance", tol);
	dict.add("relTol", relTol);

	return dict;
}


tnbLib::dictionary tnbLib::ICCG::solverDict
(
	Istream& is
)
{
	scalar tol(readScalar(is));
	scalar relTol(readScalar(is));

	return solverDict(tol, relTol);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ICCG::ICCG
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	PCG
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		dict
	)
{}


tnbLib::ICCG::ICCG
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
	PCG
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
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(lduPreconditioner, symMatrix);
	defineRunTimeSelectionTable(lduPreconditioner, asymMatrix);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::lduPreconditioner>
tnbLib::lduPreconditioner::New
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict,
	const word keyword
)
{
	word preconName;

	// handle primitive or dictionary entry
	const entry& e = dict.lookupEntry(keyword, false, false);
	if (e.isDict())
	{
		e.dict().lookup(keyword) >> preconName;
	}
	else
	{
		e.stream() >> preconName;
	}

	const dictionary& controls = e.isDict() ? e.dict() : dictionary::null;

	if (matrix.symmetric())
	{
		symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(preconName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduPreconditioner::New\n"
				"(\n"
				"    const lduMatrix& matrix,\n"
				"    const FieldField<Field, scalar>& coupleBouCoeffs,\n"
				"    const FieldField<Field, scalar>& coupleIntCoeffs,\n"
				"    const lduInterfaceFieldPtrsList& interfaces,\n"
				"    const dictionary& dict,\n"
				"    const word keyword\n"
				")",
				dict
			) << "Unknown symmetric matrix preconditioner "
				<< preconName << endl << endl
				<< "Valid symmetric matrix preconditioners are :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduPreconditioner>
			(
				constructorIter()
				(
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces,
					controls
					)
				);
	}
	else if (matrix.asymmetric())
	{
		asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(preconName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduPreconditioner::New\n"
				"(\n"
				"    const lduMatrix& matrix,\n"
				"    const FieldField<Field, scalar>& coupleBouCoeffs,\n"
				"    const FieldField<Field, scalar>& coupleIntCoeffs,\n"
				"    const lduInterfaceFieldPtrsList& interfaces,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown asymmetric matrix preconditioner "
				<< preconName << endl << endl
				<< "Valid asymmetric matrix preconditioners are :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduPreconditioner>
			(
				constructorIter()
				(
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces,
					controls
					)
				);
	}
	else
	{
		FatalIOErrorIn
		(
			"lduPreconditioner::New\n"
			"(\n"
			"    const lduMatrix& matrix,\n"
			"    const FieldField<Field, scalar>& coupleBouCoeffs,\n"
			"    const FieldField<Field, scalar>& coupleIntCoeffs,\n"
			"    const lduInterfaceFieldPtrsList& interfaces,\n"
			"    const dictionary& dict\n"
			")",
			dict
		) << "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<lduPreconditioner>(NULL);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::lduMatrix::preconditioner::preconditioner
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	matrix_(matrix),
	coupleBouCoeffs_(coupleBouCoeffs),
	coupleIntCoeffs_(coupleIntCoeffs),
	interfaces_(interfaces)
{}


// ************************************************************************* //

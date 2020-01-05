#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(lduSmoother, symMatrix);
	defineRunTimeSelectionTable(lduSmoother, asymMatrix);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::lduMatrix::smoother> tnbLib::lduMatrix::smoother::New
(
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict,
	const word keyword
)
{
	word smootherName;

	// Handle primitive or dictionary entry
	const entry& e = dict.lookupEntry(keyword, false, false);
	if (e.isDict())
	{
		e.dict().lookup(keyword) >> smootherName;
	}
	else
	{
		e.stream() >> smootherName;
	}

	// Not (yet?) needed:
	// const dictionary& controls = e.isDict() ? e.dict() : dictionary::null;

	if (matrix.symmetric())
	{
		symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(smootherName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduMatrix::smoother::New\n"
				"(\n"
				"    const lduMatrix& matrix,\n"
				"    const FieldField<Field, scalar>& coupleBouCoeffs,\n"
				"    const FieldField<Field, scalar>& coupleIntCoeffs,\n"
				"    const lduInterfaceFieldPtrsList& interfaces,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown symmetric matrix smoother " << smootherName
				<< endl << endl
				<< "Valid symmetric matrix smoothers are :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduSmoother>
			(
				constructorIter()
				(
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces
					)
				);
	}
	else if (matrix.asymmetric())
	{
		asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(smootherName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"lduMatrix::smoother::New\n"
				"(\n"
				"    const lduMatrix& matrix,\n"
				"    const FieldField<Field, scalar>& coupleBouCoeffs,\n"
				"    const FieldField<Field, scalar>& coupleIntCoeffs,\n"
				"    const lduInterfaceFieldPtrsList& interfaces,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown asymmetric matrix smoother " << smootherName
				<< endl << endl
				<< "Valid asymmetric matrix smoothers are :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduSmoother>
			(
				constructorIter()
				(
					matrix,
					coupleBouCoeffs,
					coupleIntCoeffs,
					interfaces
					)
				);
	}
	else
	{
		FatalIOErrorIn
		(
			"lduMatrix::smoother::New\n"
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

		return autoPtr<lduSmoother>(NULL);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::lduMatrix::smoother::smoother
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
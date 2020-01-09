#include <BlockLduSolver.hxx>

#include <dictionary.hxx>
#include <BlockDiagonalSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::scalar tnbLib::BlockLduSolver<Type>::great_ = 1.0e+20;

template<class Type>
const tnbLib::scalar tnbLib::BlockLduSolver<Type>::small_ = 1.0e-20;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
template<class T>
void tnbLib::BlockLduSolver<Type>::readControl
(
	const dictionary& dict,
	T& control,
	const word& controlName
)
{
	if (dict.found(controlName))
	{
		dict.lookup(controlName) >> control;
	}
	else
	{
		FatalIOErrorIn
		(
			"void BlockLduSolver<Type>::readControl::readControl\n"
			"(\n"
			"    const dictionary& dict,\n"
			"    T& control,\n"
			"    const word& controlName\n"
			")",
			dict
		) << "Cannot read control " << controlName
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockLduSolver<Type>::BlockLduSolver
(
	const word& fieldName,
	const BlockLduMatrix<Type>& matrix
)
	:
	fieldName_(fieldName),
	dict_(),
	matrix_(matrix)
{}


template<class Type>
tnbLib::BlockLduSolver<Type>::BlockLduSolver
(
	const word& fieldName,
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
	:
	fieldName_(fieldName),
	dict_(dict),
	matrix_(matrix)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<typename tnbLib::BlockLduSolver<Type> >
tnbLib::BlockLduSolver<Type>::New
(
	const word& fieldName,
	BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
{
	word solverName(dict.lookup("solver"));

	if (matrix.diagonal())
	{
		return autoPtr<BlockLduSolver<Type> >
			(
				new BlockDiagonalSolver<Type>(fieldName, matrix, dict)
				);
	}
	else if (matrix.symmetric() || matrix.asymmetric())
	{
		return BlockLduSolver<Type>::New
		(
			solverName,
			fieldName,
			matrix,
			dict
		);
	}
	else
	{
		FatalErrorIn
		(
			"BlockLduSolver<Type>::New\n"
			"(\n"
			"    const word& fieldName,\n"
			"    BlockLduMatrix<Type>& matrix,\n"
			"    const dictionary& dict\n"
			")"
		) << "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalError);

		return autoPtr<BlockLduSolver<Type> >(NULL);
	}
}


template<class Type>
tnbLib::autoPtr<typename tnbLib::BlockLduSolver<Type> >
tnbLib::BlockLduSolver<Type>::New
(
	const word& solverName,
	const word& fieldName,
	BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
{
	if (matrix.diagonal())
	{
		return autoPtr<BlockLduSolver<Type> >
			(
				new BlockDiagonalSolver<Type>(fieldName, matrix, dict)
				);
	}
	else if (matrix.symmetric())
	{
		if (!symMatrixConstructorTablePtr_)
		{
			FatalErrorIn
			(
				"BlockLduSolver<Type>::New\n"
				"(\n"
				"    const word& fieldName,\n"
				"    BlockLduMatrix<Type>& matrix,\n"
				"    const dictionary& dict\n"
				")"
			) << "Initialization problem." << endl;
		}

		typename symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"BlockLduSolver<Type>::New\n"
				"(\n"
				"    const word& solverName,\n"
				"    const word& fieldName,\n"
				"    BlockLduMatrix<Type>& matrix,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown symmetric matrix solver " << solverName
				<< endl << endl
				<< "Valid symmetric matrix solvers are :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<BlockLduSolver<Type> >
			(
				constructorIter()
				(
					fieldName,
					matrix,
					dict
					)
				);
	}
	else if (matrix.asymmetric())
	{
		if (!asymMatrixConstructorTablePtr_)
		{
			FatalErrorIn
			(
				"BlockLduSolver<Type>::New\n"
				"(\n"
				"    const word& solverName,\n"
				"    const word& fieldName,\n"
				"    BlockLduMatrix<Type>& matrix,\n"
				"    const dictionary& dict\n"
				")"
			) << "Initialization problem." << endl;
		}

		typename asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"BlockLduSolver<Type>::New\n"
				"(\n"
				"    const word& solverName,\n"
				"    const word& fieldName,\n"
				"    BlockLduMatrix<Type>& matrix,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown asymmetric matrix solver " << solverName
				<< endl << endl
				<< "Valid asymmetric matrix solvers are :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<BlockLduSolver<Type> >
			(
				constructorIter()
				(
					fieldName,
					matrix,
					dict
					)
				);
	}
	else
	{
		FatalErrorIn
		(
			"BlockLduSolver<Type>::New\n"
			"(\n"
			"    const word& solverName,\n"
			"    const word& fieldName,\n"
			"    BlockLduMatrix<Type>& matrix,\n"
			"    const dictionary& dict\n"
			")"
		) << "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalError);

		return autoPtr<BlockLduSolver<Type> >(NULL);
	}
}


// ************************************************************************* //
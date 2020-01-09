#include <BlockMatrixCoarsening.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::BlockMatrixCoarsening<Type> >
tnbLib::BlockMatrixCoarsening<Type>::New
(
	const word& coarseningType,
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict,
	const label groupSize,
	const label nCoarseCells
)
{
	typename matrixConstructorTable::iterator constructorIter =
		matrixConstructorTablePtr_->find(coarseningType);

	if (constructorIter == matrixConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"autoPtr<BlockMatrixCoarsening<Type> > "
			"BlockMatrixCoarsening<Type>::New\n"
			"(\n"
			"    const word& coarseningType,\n"
			"    const lduMatrix& matrix,\n"
			"    const label groupSize\n"
			"    const label nCoarseCells\n"
			")"
		) << "Unknown AMG coarsening type. " << coarseningType
			<< endl << endl
			<< "Valid AMG coarsening types are :" << endl
			<< matrixConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<BlockMatrixCoarsening<Type> >
		(
			constructorIter()
			(
				matrix,
				dict,
				groupSize,
				nCoarseCells
				)
			);
}


// ************************************************************************* //
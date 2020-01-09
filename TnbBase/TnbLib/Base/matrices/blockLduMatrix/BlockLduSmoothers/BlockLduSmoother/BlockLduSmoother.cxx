#include <BlockLduSmoother.hxx>

#include <entry.hxx>
#include <dictionary.hxx>

template<class Type>
class BlockNoSmoother;

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::BlockLduSmoother<Type> > tnbLib::BlockLduSmoother<Type>::New
(
	const BlockLduMatrix<Type>& matrix,
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

	const dictionary& controls = e.isDict() ? e.dict() : dictionary::null;

	typename dictionaryConstructorTable::iterator constructorIter =
		dictionaryConstructorTablePtr_->find(smootherName);

	if (constructorIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"autoPtr<BlockLduSmoother> BlockLduSmoother::New\n"
			"(\n"
			"    const BlockLduMatrix<Type>& matrix,\n"
			"    const dictionary& dict,\n"
			"    const word keyword\n"
			")",
			dict
		) << "Unknown matrix smoother " << smootherName
			<< endl << endl
			<< "Valid matrix smoothers are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<BlockLduSmoother<Type> >
		(
			constructorIter()
			(
				matrix,
				controls
				)
			);
}


// ************************************************************************* //
#include <BlockLduPrecon.hxx>

#include <entry.hxx>
#include <dictionary.hxx>
#include <blockNoPrecons.hxx>

//template<class Type>
//class BlockNoPrecon;

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::BlockLduPrecon<Type> > tnbLib::BlockLduPrecon<Type>::New
(
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict,
	const word keyword
)
{
	word preconName;

	// Handle primitive or dictionary entry
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

	if (matrix.diagonal())
	{
		// No preconditioning for the diagonal matrix
		return autoPtr<BlockLduPrecon<Type> >
			(
				new BlockNoPrecon<Type>
				(
					matrix,
					controls
					)
				);
	}
	else
	{
		typename dictionaryConstructorTable::iterator constructorIter =
			dictionaryConstructorTablePtr_->find(preconName);

		if (constructorIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"autoPtr<BlockLduPrecon> BlockLduPrecon::New\n"
				"(\n"
				"    const BlockLduMatrix<Type>& matrix,\n"
				"    const dictionary& dict\n"
				")",
				dict
			) << "Unknown matrix preconditioner " << preconName
				<< endl << endl
				<< "Valid matrix preconditioners are :" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<BlockLduPrecon<Type> >
			(
				constructorIter()
				(
					matrix,
					controls
					)
				);
	}
}


// ************************************************************************* //
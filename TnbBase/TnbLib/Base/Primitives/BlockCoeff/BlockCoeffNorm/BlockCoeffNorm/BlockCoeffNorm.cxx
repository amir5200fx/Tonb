#include <BlockCoeffNorm.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockCoeffNorm<Type>::BlockCoeffNorm
(
	const dictionary& dict
)
	:
	dict_(dict)
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<typename tnbLib::BlockCoeffNorm<Type> >
tnbLib::BlockCoeffNorm<Type>::New
(
	const dictionary& dict
)
{
	word normName(dict.lookup("norm"));

	typename dictionaryConstructorTable::iterator constructorIter =
		dictionaryConstructorTablePtr_->find(normName);

	if (constructorIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"autoPtr<BlockCoeffNorm> BlockCoeffNorm::New\n"
			"(\n"
			"    const dictionary& dict\n"
			")",
			dict
		) << "Unknown norm " << normName
			<< endl << endl
			<< "Valid matrix norms are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<BlockCoeffNorm<Type> >
		(
			constructorIter()
			(
				dict
				)
			);
}


// ************************************************************************* //
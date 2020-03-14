#include <objectRefinement.hxx>

#include <dictionary.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	autoPtr<tnbLib::objectRefinement> tnbLib::objectRefinement::New
	(
		const word& name,
		const dictionary& dict
	)
	{
		if (debug)
		{
			Info << "objectRefinement::New(const word&, const dictionary&) : "
				<< "constructing objectRefinement"
				<< endl;
		}

		// default type is self
		word refType(typeName_());
		if (dict.found("type"))
		{
			dict.lookup("type") >> refType;
		}

		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(refType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"objectRefinement::New(const word&, const dictionary&)",
				dict
			) << "Unknown objectRefinement type " << refType << nl << nl
				<< "Valid objectRefinement types are :" << nl
				<< "[default: " << typeName_() << "]"
				<< dictionaryConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<objectRefinement>(cstrIter()(name, dict));
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
#include <coordinateModification.hxx>

#include <dictionary.hxx>
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	autoPtr<tnbLib::coordinateModification> tnbLib::coordinateModification::New
	(
		const word& name,
		const dictionary& dict
	)
	{
		if (debug)
		{
			Info << "coordinateModification::New(const word&, const dictionary&) : "
				<< "constructing coordinateModification"
				<< endl;
		}

		// default type is self
		word cmType(typeName_());
		if (dict.found("type"))
		{
			dict.lookup("type") >> cmType;
		}

		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(cmType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"coordinateModification::New(const word&, const dictionary&)",
				dict
			) << "Unknown coordinateModification type " << cmType << nl << nl
				<< "Valid coordinateModification types are :" << nl
				<< "[default: " << typeName_() << "]"
				<< dictionaryConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<coordinateModification>(cstrIter()(name, dict));
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //

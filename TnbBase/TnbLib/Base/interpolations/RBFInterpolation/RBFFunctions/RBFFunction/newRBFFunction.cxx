#include <RBFFunction.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	autoPtr<RBFFunction> RBFFunction::New
	(
		const word& type,
		const dictionary& dict
	)
	{
		Info << "Radial Basis Function interpolation: "
			<< "Selecting RBF function: " << type << endl;

		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(type);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"RBFFunction::New(const word& type, const dictionary& dict)",
				dict
			) << "Unknown RBFFunction type "
				<< type << endl << endl
				<< "Valid  RBFFunctions are : " << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<RBFFunction>(cstrIter()(dict.subDict(type + "Coeffs")));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
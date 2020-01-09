#include <faceZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::faceZone> tnbLib::faceZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const faceZoneMesh& zm
)
{
	if (debug)
	{
		Info << "faceZone::New(const word&, const dictionary&, const label, "
			"const faceZoneMesh&) : constructing faceZone " << name
			<< endl;
	}

	word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"faceZone::New(const word&, const dictionary&, "
			"const label, const faceZoneMesh&)",
			dict
		) << "Unknown faceZone type " << zoneType << endl << endl
			<< "Valid faceZone types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<faceZone>(cstrIter()(name, dict, index, zm));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //
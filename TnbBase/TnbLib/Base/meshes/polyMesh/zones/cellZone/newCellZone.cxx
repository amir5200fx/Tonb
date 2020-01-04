#include <cellZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::cellZone> tnbLib::cellZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const cellZoneMesh& zm
)
{
	if (debug)
	{
		Info << "cellZone::New(const word&, const dictionary&, const label, "
			"const cellZoneMesh&) : constructing cellZone " << name
			<< endl;
	}

	word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"cellZone::New(const word&, const dictionary&, "
			"const label, const cellZoneMesh&)",
			dict
		) << "Unknown cellZone type " << zoneType << endl << endl
			<< "Valid cellZone types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<cellZone>(cstrIter()(name, dict, index, zm));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //
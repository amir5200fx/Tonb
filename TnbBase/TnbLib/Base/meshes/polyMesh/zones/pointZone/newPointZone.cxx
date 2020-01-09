#include <pointZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::pointZone> tnbLib::pointZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const pointZoneMesh& zm
)
{
	if (debug)
	{
		Info << "pointZone::New(const word&, const dictionary&, const label, "
			"const pointZoneMesh&) : constructing pointZone " << name
			<< endl;
	}

	word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"pointZone::New(const word&, const dictionary&, "
			"const label, const pointZoneMesh&)",
			dict
		) << "Unknown pointZone type " << zoneType << endl << endl
			<< "Valid pointZone types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<pointZone>(cstrIter()(name, dict, index, zm));
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //
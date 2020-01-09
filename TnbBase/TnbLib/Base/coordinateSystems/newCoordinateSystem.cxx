#include <coordinateSystem.hxx>

#include <dictionary.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	const word& name,
	const dictionary& dict
)
{
	if (debug)
	{
		Pout << "coordinateSystem::New(const word&, const dictionary&) : "
			<< "constructing coordinateSystem"
			<< endl;
	}

	// construct base class directly, also allow 'cartesian' as an alias
	word coordType(typeName_());
	if
		(
			!dict.readIfPresent("type", coordType)
			|| coordType == typeName_()
			|| coordType == "cartesian"
			)
	{
		return autoPtr<coordinateSystem>(new coordinateSystem(name, dict));
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(coordType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorIn
		(
			"coordinateSystem::New(const word&, const dictionary&)",
			dict
		) << "Unknown coordinateSystem type " << coordType << nl << nl
			<< "Valid coordinateSystem types are :" << nl
			<< "[default: " << typeName_() << "]"
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<coordinateSystem>(cstrIter()(name, dict));
}


tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	const word& coordType,
	const word& name,
	const point& origin,
	const coordinateRotation& cr
)
{
	if (debug)
	{
		Pout << "coordinateSystem::New(const word&, const word&, "
			<< "const point&, const coordinateRotation&) : "
			"constructing coordinateSystem"
			<< endl;
	}

	origRotationConstructorTable::iterator cstrIter =
		origRotationConstructorTablePtr_->find(coordType);

	if (cstrIter == origRotationConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"coordinateSystem::New(const word&, const word&, "
			"const point&, const coordinateRotation&) : "
			"constructing coordinateSystem"
		) << "Unknown coordinateSystem type " << coordType << nl << nl
			<< "Valid coordinateSystem types are :" << nl
			<< origRotationConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<coordinateSystem>(cstrIter()(name, origin, cr));
}


tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	Istream& is
)
{
	word name(is);
	dictionary dict(is);

	return New(name, dict);
}

// ************************************************************************* //

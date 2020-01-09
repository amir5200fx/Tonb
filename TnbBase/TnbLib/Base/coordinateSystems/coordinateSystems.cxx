#include <coordinateSystems.hxx>

#include <IOPtrList.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coordinateSystems, 0);
	defineTemplateTypeNameAndDebug(IOPtrList<coordinateSystem>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coordinateSystems::coordinateSystems(const IOobject& io)
	:
	IOPtrList<coordinateSystem>(io)
{}


tnbLib::coordinateSystems::coordinateSystems
(
	const IOobject& io,
	const PtrList<coordinateSystem>& lst
)
	:
	IOPtrList<coordinateSystem>(io, lst)
{}


tnbLib::coordinateSystems::coordinateSystems
(
	const IOobject& io,
	const Xfer<PtrList<coordinateSystem> >& lst
)
	:
	IOPtrList<coordinateSystem>(io, lst)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

// Read construct from registry, or return previously registered
const tnbLib::coordinateSystems& tnbLib::coordinateSystems::New
(
	const objectRegistry& obr
)
{
	if (obr.foundObject<coordinateSystems>(typeName))
	{
		return obr.lookupObject<coordinateSystems>(typeName);
	}
	else
	{
		return obr.store
		(
			new coordinateSystems
			(
				IOobject
				(
					typeName,
					"constant",
					obr,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				)
			)
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::coordinateSystems::find(const word& keyword) const
{
	forAll(*this, i)
	{
		if (keyword == operator[](i).name())
		{
			return i;
		}
	}

	return -1;
}


bool tnbLib::coordinateSystems::found(const word& keyword) const
{
	return find(keyword) >= 0;
}


tnbLib::wordList tnbLib::coordinateSystems::toc() const
{
	wordList keywords(size());

	forAll(*this, i)
	{
		keywords[i] = operator[](i).name();
	}

	return keywords;
}


bool tnbLib::coordinateSystems::writeData(Ostream& os, bool subDict) const
{
	os << nl << size() << nl << token::BEGIN_LIST;

	forAll(*this, i)
	{
		os << nl;
		operator[](i).writeDict(os, subDict);
	}

	os << token::END_LIST << nl;

	return os.good();
}


// ************************************************************************* //

#include <patchIdentifier.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchIdentifier::patchIdentifier
(
	const word& name,
	const label index,
	const word& physicalType
)
	:
	name_(name),
	index_(index),
	physicalType_(physicalType)
{}


tnbLib::patchIdentifier::patchIdentifier
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	name_(name),
	index_(index)
{
	dict.readIfPresent("physicalType", physicalType_);
}


tnbLib::patchIdentifier::patchIdentifier
(
	const patchIdentifier& p,
	const label index
)
	:
	name_(p.name_),
	index_(index),
	physicalType_(p.physicalType_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchIdentifier::~patchIdentifier()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::patchIdentifier::write(Ostream& os) const
{
	if (physicalType_.size())
	{
		os.writeKeyword("physicalType") << physicalType_
			<< token::END_STATEMENT << nl;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const patchIdentifier& pi)
{
	pi.write(os);
	os.check("Ostream& operator<<(Ostream&, const patchIdentifier&)");
	return os;
}


// ************************************************************************* //
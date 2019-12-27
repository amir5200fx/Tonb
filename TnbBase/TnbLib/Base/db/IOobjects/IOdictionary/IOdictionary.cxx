#include <IOdictionary.hxx>

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::IOdictionary, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOdictionary::IOdictionary(const IOobject& io)
	: regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}

	dictionary::name() = IOobject::objectPath();
}


tnbLib::IOdictionary::IOdictionary(const IOobject& io, const dictionary& dict)
	: regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
	else
	{
		dictionary::operator=(dict);
	}

	dictionary::name() = IOobject::objectPath();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::IOdictionary::~IOdictionary()
{}


// * * * * * * * * * * * * * * * Members Functions * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::IOdictionary::name() const
{
	return regIOobject::name();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::IOdictionary::operator=(const IOdictionary& rhs)
{
	dictionary::operator=(rhs);
}


// ************************************************************************* //
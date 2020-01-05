#include <cloud.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::cloud, 0);

const tnbLib::word tnbLib::cloud::prefix("lagrangian");
tnbLib::word tnbLib::cloud::defaultName("defaultCloud");

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cloud::cloud(const objectRegistry& obr, const word& cloudName)
	:
	objectRegistry
	(
		IOobject
		(
		(cloudName.size() ? cloudName : defaultName),
			obr.time().timeName(),
			prefix,
			obr,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cloud::~cloud()
{}


// ************************************************************************* //
#include <regIOobject.hxx>

#include <objectRegistry.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::regIOobject, 0);

const tnbLib::debug::optimisationSwitch
tnbLib::regIOobject::fileModificationSkew
(
	"fileModificationSkew",
	30
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from IOobject
tnbLib::regIOobject::regIOobject(const IOobject& io, const bool isTime)
	:
	IOobject(io),
	registered_(false),
	ownedByRegistry_(false),
	lastModified_(0),
	eventNo_                // Do not get event for top level Time database
	(
		isTime
		? 0
		: db().getEvent()
	),
	isPtr_(NULL)
{
	// Register with objectRegistry if requested
	if (registerObject())
	{
		checkIn();
	}
}


// Construct as copy
tnbLib::regIOobject::regIOobject(const regIOobject& rio)
	:
	IOobject(rio),
	registered_(false),
	ownedByRegistry_(false),
	lastModified_(rio.lastModified_),
	eventNo_(db().getEvent()),
	isPtr_(NULL)
{
	// Do not register copy with objectRegistry
}


// Construct as copy, and transfering objectRegistry registration to copy
// if registerCopy is true
tnbLib::regIOobject::regIOobject(const regIOobject& rio, bool registerCopy)
	:
	IOobject(rio),
	registered_(false),
	ownedByRegistry_(false),
	lastModified_(rio.lastModified_),
	eventNo_(db().getEvent()),
	isPtr_(NULL)
{
	if (registerCopy && rio.registered_)
	{
		const_cast<regIOobject&>(rio).checkOut();
		checkIn();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

// Delete read stream, checkout from objectRegistry and destroy
tnbLib::regIOobject::~regIOobject()
{
	if (objectRegistry::debug)
	{
		Info << "Destroying regIOobject called " << name()
			<< " of type " << type()
			<< " in directory " << path()
			<< endl;
	}

	if (isPtr_)
	{
		delete isPtr_;
		isPtr_ = NULL;
	}

	// Check out of objectRegistry if not owned by the registry

	if (!ownedByRegistry_)
	{
		checkOut();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::regIOobject::checkIn()
{
	if (!registered_)
	{
		// multiple checkin of same object is disallowed - this would mess up
		// any mapping
		registered_ = db().checkIn(*this);

		// check-in on defaultRegion is allowed to fail, since subsetted meshes
		// are created with the same name as their originating mesh
		if (!registered_ && debug && name() != polyMesh::defaultRegion)
		{
			if (debug == 2)
			{
				// for ease of finding where attempted duplicate check-in
				// originated
				FatalErrorIn("regIOobject::checkIn()")
					<< "failed to register object " << objectPath()
					<< " the name already exists in the objectRegistry"
					<< abort(FatalError);
			}
			else
			{
				WarningIn("regIOobject::checkIn()")
					<< "failed to register object " << objectPath()
					<< " the name already exists in the objectRegistry"
					<< endl;
			}
		}
	}

	return registered_;
}


bool tnbLib::regIOobject::checkOut()
{
	if (registered_)
	{
		registered_ = false;
		return db().checkOut(*this);
	}

	return false;
}


bool tnbLib::regIOobject::upToDate(const word& a) const
{
	if (db().lookupObject<regIOobject>(a).eventNo() >= eventNo_)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate(const word& a, const word& b) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate
(
	const word& a,
	const word& b,
	const word& c
) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(c).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate
(
	const word& a,
	const word& b,
	const word& c,
	const word& d
) const
{
	if
		(
			db().lookupObject<regIOobject>(a).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(b).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(c).eventNo() >= eventNo_
			|| db().lookupObject<regIOobject>(d).eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//- Flag me as up to date
void tnbLib::regIOobject::setUpToDate()
{
	eventNo_ = db().getEvent();
}


// Rename object and re-register with objectRegistry under new name
void tnbLib::regIOobject::rename(const word& newName)
{
	// Check out of objectRegistry
	checkOut();

	IOobject::rename(newName);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}


// Assign to IOobject
void tnbLib::regIOobject::operator=(const IOobject& io)
{
	if (isPtr_)
	{
		delete isPtr_;
		isPtr_ = NULL;
	}

	// Check out of objectRegistry
	checkOut();

	IOobject::operator=(io);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}


// ************************************************************************* //
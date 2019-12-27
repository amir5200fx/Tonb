#include <objectRegistry.hxx>

#include <tnbTime.hxx>
#include <OPstream.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::objectRegistry, 0);


// * * * * * * * * * * * * * * * * Constructors *  * * * * * * * * * * * * * //

tnbLib::objectRegistry::objectRegistry
(
	const Time& t,
	const label nIoObjects
)
	: regIOobject
	(
		IOobject
		(
			string::validate<word>(t.caseName()),
			t,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		true    // to flag that this is the top-level regIOobject
	),
	HashTable<regIOobject*>(nIoObjects),
	time_(t),
	parent_(t),
	dbDir_(name()),
	event_(1)
{}


tnbLib::objectRegistry::objectRegistry
(
	const IOobject& io,
	const label nIoObjects
)
	:
	regIOobject(io),
	HashTable<regIOobject*>(nIoObjects),
	time_(io.time()),
	parent_(io.db()),
	dbDir_(parent_.dbDir() / local() / name()),
	event_(1)
{
	writeOpt() = IOobject::AUTO_WRITE;
}


tnbLib::objectRegistry::objectRegistry
(
	const IOobject& io,
	const fileName& dbDir,
	const label nIoObjects
)
	:
	regIOobject(io),
	HashTable<regIOobject*>(nIoObjects),
	time_(io.time()),
	parent_(io.db()),
	dbDir_(dbDir),
	event_(1)
{
	writeOpt() = IOobject::AUTO_WRITE;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::objectRegistry::~objectRegistry()
{
	List<regIOobject*> myObjects(size());
	label nMyObjects = 0;

	for (iterator iter = begin(); iter != end(); ++iter)
	{
		if (iter()->ownedByRegistry())
		{
			myObjects[nMyObjects++] = iter();
		}
	}

	for (label i = 0; i < nMyObjects; i++)
	{
		checkOut(*myObjects[i]);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::Time& tnbLib::objectRegistry::time() const
{
	return time_;
}


tnbLib::wordList tnbLib::objectRegistry::names() const
{
	wordList objectNames(size());

	label count = 0;
	for (const_iterator iter = cbegin(); iter != cend(); ++iter)
	{
		objectNames[count++] = iter()->name();
	}

	return objectNames;
}


tnbLib::wordList tnbLib::objectRegistry::names(const word& ClassName) const
{
	wordList objectNames(size());

	label count = 0;
	for (const_iterator iter = cbegin(); iter != cend(); ++iter)
	{
		if (iter()->type() == ClassName)
		{
			objectNames[count++] = iter()->name();
		}
	}

	objectNames.setSize(count);

	return objectNames;
}


tnbLib::fileName tnbLib::objectRegistry::mangleFileName
(
	const fileName& fName
) const
{
	return fName;
}


const tnbLib::objectRegistry& tnbLib::objectRegistry::subRegistry
(
	const word& name
) const
{
	return lookupObject<objectRegistry>(name);
}


tnbLib::label tnbLib::objectRegistry::getEvent() const
{
	label curEvent = event_++;

	if (event_ == labelMax)
	{
		WarningIn("objectRegistry::getEvent() const")
			<< "Event counter has overflowed. Resetting counter on all"
			<< " dependent objects." << endl
			<< "This might cause extra evaluations." << endl;

		// Reset event counter
		curEvent = 1;
		event_ = 2;

		for (const_iterator iter = begin(); iter != end(); ++iter)
		{
			const regIOobject& io = *iter();

			if (objectRegistry::debug)
			{
				Pout << "objectRegistry::getEvent() : "
					<< "resetting count on " << iter.key() << endl;
			}

			if (io.eventNo() != 0)
			{
				const_cast<regIOobject&>(io).eventNo() = curEvent;
			}
		}
	}

	return curEvent;
}


bool tnbLib::objectRegistry::checkIn(regIOobject& io) const
{
	if (objectRegistry::debug)
	{
		Pout << "objectRegistry::checkIn(regIOobject&) : "
			<< name() << " : checking in " << io.name()
			<< endl;
	}

	return const_cast<objectRegistry&>(*this).insert(io.name(), &io);
}


bool tnbLib::objectRegistry::checkOut(regIOobject& io) const
{
	iterator iter = const_cast<objectRegistry&>(*this).find(io.name());

	if (iter != end())
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::checkOut(regIOobject&) : "
				<< name() << " : checking out " << io.name()
				<< endl;
		}

		if (iter() != &io)
		{
			if (objectRegistry::debug)
			{
				WarningIn("objectRegistry::checkOut(regIOobject&)")
					<< name() << " : attempt to checkOut copy of " << io.name()
					<< endl;
			}

			return false;
		}
		else
		{
			regIOobject* object = iter();

			bool hasErased = const_cast<objectRegistry&>(*this).erase(iter);

			if (io.ownedByRegistry())
			{
				delete object;
			}

			return hasErased;
		}
	}
	else
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::checkOut(regIOobject&) : "
				<< name() << " : could not find " << io.name()
				<< " in registry " << name()
				<< endl;
		}
	}

	return false;
}


void tnbLib::objectRegistry::rename(const word& newName)
{
	regIOobject::rename(newName);

	// adjust dbDir_ as well
	string::size_type i = dbDir_.rfind('/');

	if (i == string::npos)
	{
		dbDir_ = newName;
	}
	else
	{
		dbDir_.replace(i + 1, string::npos, newName);
	}
}


bool tnbLib::objectRegistry::modified() const
{
	for (const_iterator iter = cbegin(); iter != cend(); ++iter)
	{
		if (iter()->modified())
		{
			return true;
		}
	}

	return false;
}


void tnbLib::objectRegistry::readModifiedObjects()
{
	for (iterator iter = begin(); iter != end(); ++iter)
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::readModifiedObjects() : "
				<< name() << " : Considering reading object "
				<< iter()->name()
				<< endl;
		}

		iter()->readIfModified();
	}
}


bool tnbLib::objectRegistry::readIfModified()
{
	readModifiedObjects();
	return true;
}


bool tnbLib::objectRegistry::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp
) const
{
	bool ok = true;

	for (const_iterator iter = cbegin(); iter != cend(); ++iter)
	{
		if (objectRegistry::debug)
		{
			Pout << "objectRegistry::write() : "
				<< name() << " : Considering writing object "
				<< iter()->name()
				<< " with writeOpt " << iter()->writeOpt()
				<< " to file " << iter()->objectPath()
				<< endl;
		}

		if (iter()->writeOpt() != NO_WRITE)
		{
			ok = iter()->writeObject(fmt, ver, cmp) && ok;
		}
	}

	return ok;
}


// ************************************************************************* //
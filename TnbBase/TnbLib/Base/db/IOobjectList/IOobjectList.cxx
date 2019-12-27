#include <IOobjectList.hxx>

#include <objectRegistry.hxx>
#include <OSspecific.hxx>
#include <instant.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOobjectList::IOobjectList(const label nIoObjects)
	: HashPtrTable<IOobject>(nIoObjects)
{}


tnbLib::IOobjectList::IOobjectList
(
	const objectRegistry& db,
	const fileName& instance,
	const fileName& local
)
	:
	HashPtrTable<IOobject>()
{
	word newInstance = instance;

	if (!isDir(db.path(instance)))
	{
		newInstance = db.time().findInstancePath(instant(instance));

		if (newInstance.empty())
		{
			return;
		}
	}

	// Create list file names in directory
	fileNameList ObjectNames =
		readDir(db.path(newInstance, db.dbDir() / local), fileName::FILE);

	forAll(ObjectNames, i)
	{
		IOobject* objectPtr = new IOobject
		(
			ObjectNames[i],
			newInstance,
			local,
			db,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		);

		if (objectPtr->headerOk())
		{
			insert(ObjectNames[i], objectPtr);
		}
		else
		{
			delete objectPtr;
		}
	}
}


tnbLib::IOobjectList::IOobjectList(const IOobjectList& ioOL)
	:
	HashPtrTable<IOobject>(ioOL)
{}


// * * * * * * * * * * * * * * * * Destructors * * * * * * * * * * * * * * * //

tnbLib::IOobjectList::~IOobjectList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::IOobjectList::add(IOobject& io)
{
	return insert(io.name(), &io);
}


bool tnbLib::IOobjectList::remove(IOobject& io)
{
	HashPtrTable<IOobject>::iterator iter =
		HashPtrTable<IOobject>::find(io.name());

	if (iter != end())
	{
		return erase(iter);
	}
	else
	{
		return false;
	}
}


tnbLib::IOobject* tnbLib::IOobjectList::lookup(const word& name) const
{
	HashPtrTable<IOobject>::const_iterator iter = find(name);

	if (iter != end())
	{
		if (IOobject::debug)
		{
			Info << "IOobjectList::lookup : found " << name
				<< endl;
		}

		return const_cast<IOobject*>(*iter);
	}
	else
	{
		if (IOobject::debug)
		{
			Info << "IOobjectList::lookup : could not find " << name
				<< endl;
		}

		return NULL;
	}
}


tnbLib::IOobjectList tnbLib::IOobjectList::lookupClass(const word& ClassName) const
{
	IOobjectList IOobjectsOfClass(size());

	for
		(
			HashPtrTable<IOobject>::const_iterator iter = begin();
			iter != end();
			++iter
			)
	{
		if (iter()->headerClassName() == ClassName)
		{
			if (IOobject::debug)
			{
				Info << "IOobjectList::lookupClass : found "
					<< iter()->name()
					<< endl;
			}

			IOobjectsOfClass.insert(iter()->name(), new IOobject(*iter()));
		}
	}

	return IOobjectsOfClass;
}


tnbLib::wordList tnbLib::IOobjectList::names() const
{
	wordList objectNames(size());

	label count = 0;
	for
		(
			HashPtrTable<IOobject>::const_iterator iter = begin();
			iter != end();
			++iter
			)
	{
		objectNames[count++] = iter()->name();
	}

	return objectNames;
}


tnbLib::wordList tnbLib::IOobjectList::names(const word& ClassName) const
{
	wordList objectNames(size());

	label count = 0;
	for
		(
			HashPtrTable<IOobject>::const_iterator iter = begin();
			iter != end();
			++iter
			)
	{
		if (iter()->headerClassName() == ClassName)
		{
			objectNames[count++] = iter()->name();
		}
	}

	objectNames.setSize(count);

	return objectNames;
}


// ************************************************************************* //
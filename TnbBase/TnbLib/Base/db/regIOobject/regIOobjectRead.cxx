#include <regIOobject.hxx>

#include <IFstream.hxx>
#include <objectRegistry.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::regIOobject::readStream()
{
	if (IFstream::debug)
	{
		Info << "regIOobject::readStream() : "
			<< "reading object " << name()
			<< " from file " << objectPath()
			<< endl;
	}

	if (readOpt() == NO_READ)
	{
		FatalErrorIn("regIOobject::readStream()")
			<< "NO_READ specified for read-constructor of object " << name()
			<< " of class " << headerClassName()
			<< abort(FatalError);
	}

	// Construct object stream and read header if not already constructed
	if (!isPtr_)
	{
		if (!(isPtr_ = objectStream()))
		{
			FatalIOError
			(
				"regIOobject::readStream()",
				__FILE__,
				__LINE__,
				objectPath(),
				0
			) << "cannot open file"
				<< exit(FatalIOError);
		}
		else if (!readHeader(*isPtr_))
		{
			FatalIOErrorIn("regIOobject::readStream()", *isPtr_)
				<< "problem while reading header for object " << name()
				<< exit(FatalIOError);
		}
	}

	if (!lastModified_)
	{
		lastModified_ = lastModified(filePath());
	}

	return *isPtr_;
}


tnbLib::Istream& tnbLib::regIOobject::readStream(const word& expectName)
{
	if (IFstream::debug)
	{
		Info << "regIOobject::readStream(const word&) : "
			<< "reading object " << name()
			<< " from file " << objectPath()
			<< endl;
	}

	// Construct IFstream if not already constructed
	if (!isPtr_)
	{
		readStream();

		// Check the className of the regIOobject
		// dictionary is an allowable name in case the actual class
		// instantiated is a dictionary
		if
			(
				expectName.size()
				&& headerClassName() != expectName
				&& headerClassName() != "dictionary"
				)
		{
			FatalIOErrorIn("regIOobject::readStream(const word&)", *isPtr_)
				<< "unexpected class name " << headerClassName()
				<< " expected " << expectName << endl
				<< "    while reading object " << name()
				<< exit(FatalIOError);
		}
	}

	return *isPtr_;
}


void tnbLib::regIOobject::close()
{
	if (IFstream::debug)
	{
		Info << "regIOobject::close() : "
			<< "finished reading " << filePath()
			<< endl;
	}

	if (isPtr_)
	{
		delete isPtr_;
		isPtr_ = NULL;
	}
}


bool tnbLib::regIOobject::readData(Istream&)
{
	return false;
}


bool tnbLib::regIOobject::read()
{
	bool ok = readData(readStream(type()));
	close();
	return ok;
}


bool tnbLib::regIOobject::modified() const
{
	return
		(
			lastModified_
			&& lastModified(filePath()) > (lastModified_ + fileModificationSkew())
			);
}


bool tnbLib::regIOobject::readIfModified()
{
	if (lastModified_)
	{
		time_t newTimeStamp = lastModified(filePath());

		bool readFile = false;

		if (newTimeStamp > (lastModified_ + fileModificationSkew()))
		{
			readFile = true;
		}

		if (Pstream::parRun())
		{
			bool readFileOnThisProc = readFile;
			reduce(readFile, andOp<bool>());

			if (readFileOnThisProc && !readFile)
			{
				WarningIn("regIOobject::readIfModified()")
					<< "Delaying reading " << name()
					<< " of class " << headerClassName()
					<< " due to inconsistent "
					"file time-stamps between processors"
					<< endl;
			}
		}

		if (readFile)
		{
			lastModified_ = newTimeStamp;
			Info << "regIOobject::readIfModified() : " << nl
				<< "    Reading object " << name()
				<< " from file " << filePath() << endl;
			return read();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //
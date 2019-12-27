#include <regIOobject.hxx>

#include <objectRegistry.hxx>
#include <OSspecific.hxx>
#include <OFstream.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::regIOobject::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp
) const
{
	if (!good())
	{
		SeriousErrorIn("regIOobject::write()")
			<< "bad object " << name()
			<< endl;

		return false;
	}

	if (instance().empty())
	{
		SeriousErrorIn("regIOobject::write()")
			<< "instance undefined for object " << name()
			<< endl;

		return false;
	}

	if
		(
			instance() != time().timeName()
			&& instance() != time().system()
			&& instance() != time().caseSystem()
			&& instance() != time().constant()
			&& instance() != time().caseConstant()
			)
	{
		const_cast<regIOobject&>(*this).instance() = time().timeName();
	}

	mkDir(path());

	if (OFstream::debug)
	{
		Info << "regIOobject::write() : "
			<< "writing file " << objectPath();
	}


	bool osGood = false;

	{
		// Try opening an OFstream for object
		// Stream open for over-write.  HJ, 17/Aug/2010
		OFstream os
		(
			objectPath(),
			ios_base::out | ios_base::trunc,
			fmt,
			ver,
			cmp
		);

		// If any of these fail, return (leave error handling to Ostream class)
		if (!os.good())
		{
			return false;
		}

		if (!writeHeader(os))
		{
			return false;
		}

		// Write the data to the Ostream
		if (!writeData(os))
		{
			return false;
		}

		writeEndDivider(os);

		osGood = os.good();
	}

	if (OFstream::debug)
	{
		Info << " .... written" << endl;
	}

	// Only update the lastModified_ time if this object is re-readable,
	// i.e. lastModified_ is already set
	if (lastModified_)
	{
		lastModified_ = lastModified(objectPath());
	}

	return osGood;
}


bool tnbLib::regIOobject::write() const
{
	return writeObject
	(
		time().writeFormat(),
		IOstream::currentVersion,
		time().writeCompression()
	);
}

// ************************************************************************* //
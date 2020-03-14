#include <OFstream.hxx>

#include <OSspecific.hxx>
#include <gzstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::OFstream, 0);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::OFstreamAllocator::OFstreamAllocator
(
	const fileName& pathname,
	ios_base::openmode mode,
	IOstream::compressionType compression
)
	: ofPtr_(NULL)
{
	if (pathname.empty())
	{
		if (OFstream::debug)
		{
			Info << "OFstreamAllocator::OFstreamAllocator(const fileName&) : "
				"cannot open null file " << endl;
		}
	}

	if (compression == IOstream::COMPRESSED)
	{
		// get identically named uncompressed version out of the way
		if (isFile(pathname, false))
		{
			rm(pathname);
		}

		ofPtr_ = new ogzstream((pathname + ".gz").c_str(), mode);
	}
	else
	{
		// get identically named compressed version out of the way
		if (isFile(pathname + ".gz", false))
		{
			rm(pathname + ".gz");
		}

		ofPtr_ = new ofstream(pathname.c_str(), mode);
	}
}


tnbLib::OFstreamAllocator::~OFstreamAllocator()
{
	delete ofPtr_;
}


std::ostream& tnbLib::OFstreamAllocator::stdStream()
{
	if (!ofPtr_)
	{
		FatalErrorIn("OFstreamAllocator::stdStream()")
			<< "No stream allocated." << abort(FatalError);
	}
	return *ofPtr_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::OFstream::OFstream
(
	const fileName& pathname,
	ios_base::openmode mode,
	streamFormat format,
	versionNumber version,
	compressionType compression
)
	: OFstreamAllocator(pathname, mode, compression)
	, OSstream(*ofPtr_, "OFstream.sinkFile_", format, version, compression)
	, pathname_(pathname)
{
	setClosed();
	setState(ofPtr_->rdstate());

	if (!good())
	{
		if (debug)
		{
			Info << "IFstream::IFstream(const fileName&,"
				"streamFormat format=ASCII,"
				"versionNumber version=currentVersion) : "
				"could not open file for input\n"
				"in stream " << info() << tnbLib::endl;
		}

		setBad();
	}
	else
	{
		setOpened();
	}

	lineNumber_ = 1;
}


// * * * * * * * * * * * * * * * * Destructors * * * * * * * * * * * * * * * //

tnbLib::OFstream::~OFstream()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::OFstream::print(Ostream& os) const
{
	os << "    OFstream: ";
	OSstream::print(os);
}


// ************************************************************************* //
#include <IOobject.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::IOobject::readHeader(Istream& is)
{
	if (IOobject::debug)
	{
		Info << "IOobject::readHeader(Istream&) : reading header for file "
			<< is.name() << endl;
	}

	// Check Istream not already bad
	if (!is.good())
	{
		if (rOpt_ == MUST_READ)
		{
			FatalIOErrorIn("IOobject::readHeader(Istream&)", is)
				<< " stream not open for reading essential object from file "
				<< is.name()
				<< exit(FatalIOError);
		}

		if (IOobject::debug)
		{
			SeriousIOErrorIn("IOobject::readHeader(Istream&)", is)
				<< " stream not open for reading from file "
				<< is.name() << endl;
		}

		return false;
	}

	token firstToken(is);

	if
		(
			is.good()
			&& firstToken.isWord()
			&& firstToken.wordToken() == "FoamFile"
			)
	{
		dictionary headerDict(is);

		is.version(headerDict.lookup("version"));
		is.format(headerDict.lookup("format"));
		headerClassName_ = word(headerDict.lookup("class"));

		word headerObject(headerDict.lookup("object"));
		if (IOobject::debug && headerObject != name())
		{
			IOWarningIn("IOobject::readHeader(Istream&)", is)
				<< " object renamed from "
				<< name() << " to " << headerObject
				<< " for file " << is.name() << endl;
		}

		// The note entry is optional
		headerDict.readIfPresent("note", note_);
	}
	else
	{
		SeriousIOErrorIn("IOobject::readHeader(Istream&)", is)
			<< "First token could not be read or is not the keyword 'FoamFile'"
			<< nl << nl << "Check header is of the form:" << nl << endl;

		writeHeader(Info);

		return false;
	}

	// Check stream is still OK
	if (is.good())
	{
		objState_ = GOOD;
	}
	else
	{
		if (rOpt_ == MUST_READ)
		{
			FatalIOErrorIn("IOobject::readHeader(Istream&)", is)
				<< " stream failure while reading header"
				<< " on line " << is.lineNumber()
				<< " of file " << is.name()
				<< " for essential object" << name()
				<< exit(FatalIOError);
		}

		if (IOobject::debug)
		{
			Info << "IOobject::readHeader(Istream&) :"
				<< " stream failure while reading header"
				<< " on line " << is.lineNumber()
				<< " of file " << is.name() << endl;
		}

		objState_ = BAD;

		return false;
	}

	if (IOobject::debug)
	{
		Info << " .... read" << endl;
	}

	return true;
}


// ************************************************************************* //
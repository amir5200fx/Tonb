#include <messageStream.hxx>

#include <error.hxx>
#include <dictionary.hxx>
#include <Pstream.hxx>

#include <IOstreams.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::debug::debugSwitch
tnbLib::messageStream::level
(
	"level",
	2
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::messageStream::messageStream
(
	const string& title,
	errorSeverity sev,
	const int maxErrors
)
	:
	title_(title),
	severity_(sev),
	maxErrors_(maxErrors),
	errorCount_(0)
{}


tnbLib::messageStream::messageStream(const dictionary& dict)
	:
	title_(dict.lookup("title")),
	severity_(FATAL),
	maxErrors_(0),
	errorCount_(0)
{}


tnbLib::OSstream& tnbLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber
	)
{
	OSstream& os = operator OSstream&();

	os << endl
		<< "    From function " << functionName << endl
		<< "    in file " << sourceFileName
		<< " at line " << sourceFileLineNumber << endl
		<< "    ";

	return os;
}


tnbLib::OSstream& tnbLib::messageStream::operator()
(
	const string& functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber
	)
{
	return operator()
		(
			functionName.c_str(),
			sourceFileName,
			sourceFileLineNumber
			);
}


tnbLib::OSstream& tnbLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const string& ioFileName,
	const label ioStartLineNumber,
	const label ioEndLineNumber
	)
{
	OSstream& os = operator OSstream&();

	os << endl
		<< "    From function " << functionName << endl
		<< "    in file " << sourceFileName
		<< " at line " << sourceFileLineNumber << endl
		<< "    Reading " << ioFileName;

	if (ioStartLineNumber >= 0 && ioEndLineNumber >= 0)
	{
		os << " from line " << ioStartLineNumber
			<< " to line " << ioEndLineNumber;
	}
	else if (ioStartLineNumber >= 0)
	{
		os << " at line " << ioStartLineNumber;
	}

	os << endl << "    ";

	return os;
}


tnbLib::OSstream& tnbLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const IOstream& ioStream
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			ioStream.name(),
			ioStream.lineNumber(),
			-1
			);
}


tnbLib::OSstream& tnbLib::messageStream::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const dictionary& dict
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			dict.name(),
			dict.startLineNumber(),
			dict.endLineNumber()
			);
}


tnbLib::messageStream::operator tnbLib::OSstream&()
{
	if (level)
	{
		bool collect = (severity_ == INFO || severity_ == WARNING);

		// Report the error
		if (!Pstream::master() && collect)
		{
			return Snull;
		}
		else
		{
			if (title().size())
			{
				if (Pstream::parRun() && !collect)
				{
					Pout << title().c_str();
				}
				else
				{
					Sout << title().c_str();
				}
			}

			if (maxErrors_)
			{
				errorCount_++;

				if (errorCount_ >= maxErrors_)
				{
					FatalErrorIn("messageStream::operator OSstream&()")
						<< "Too many errors"
						<< abort(FatalError);
				}
			}

			if (Pstream::parRun() && !collect)
			{
				return Pout;
			}
			else
			{
				return Sout;
			}
		}
	}

	return Snull;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global messageStream definitions

tnbLib::messageStream tnbLib::SeriousError
(
	"--> TONB Serious Error : ",
	messageStream::SERIOUS,
	100
);

tnbLib::messageStream tnbLib::Warning
(
	"--> TONB Warning : ",
	messageStream::WARNING
);

tnbLib::messageStream tnbLib::Info("", messageStream::INFO);

bool tnbLib::writeInfoHeader = true;


// ************************************************************************* //
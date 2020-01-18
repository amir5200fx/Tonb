#include <error.hxx>

#include <token.hxx>
#include <OStringStream.hxx>
#include <fileName.hxx>
#include <dictionary.hxx>
#include <JobInfo.hxx>
#include <Pstream.hxx>
#include <OSspecific.hxx>

#include <OSstream.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::error::error(const string& title)
	:
	std::exception(),
	messageStream(title, messageStream::FATAL),
	functionName_("unknown"),
	sourceFileName_("unknown"),
	sourceFileLineNumber_(0),
	abort_(env("TONB_ABORT")),
	throwExceptions_(false),
	messageStreamPtr_(new OStringStream())
{
	if (!messageStreamPtr_->good())
	{
		Perr << endl
			<< "error::error(const string& title) : cannot open error stream"
			<< endl;
		exit(1);
	}
}


tnbLib::error::error(const dictionary& errDict)
	:
	std::exception(),
	messageStream(errDict),
	functionName_(errDict.lookup("functionName")),
	sourceFileName_(errDict.lookup("sourceFileName")),
	sourceFileLineNumber_(readLabel(errDict.lookup("sourceFileLineNumber"))),
	abort_(env("TONB_ABORT")),
	throwExceptions_(false),
	messageStreamPtr_(new OStringStream())
{
	if (!messageStreamPtr_->good())
	{
		Perr << endl
			<< "error::error(const dictionary& errDict) : "
			"cannot open error stream"
			<< endl;
		exit(1);
	}
}


tnbLib::error::error(const error& err)
	:
	std::exception(),
	messageStream(err),
	functionName_(err.functionName_),
	sourceFileName_(err.sourceFileName_),
	sourceFileLineNumber_(err.sourceFileLineNumber_),
	abort_(err.abort_),
	throwExceptions_(err.throwExceptions_),
	messageStreamPtr_(new OStringStream(*err.messageStreamPtr_))
{
	//*messageStreamPtr_ << err.message();
}


tnbLib::error::~error() throw()
{
	delete messageStreamPtr_;
}


tnbLib::OSstream& tnbLib::error::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber
	)
{
	functionName_ = functionName;
	sourceFileName_ = sourceFileName;
	sourceFileLineNumber_ = sourceFileLineNumber;

	return operator OSstream&();
}


tnbLib::OSstream& tnbLib::error::operator()
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

namespace tnbLib
{
	error::operator OSstream&()
	{
		if (!messageStreamPtr_->good())
		{
			Perr << endl
				<< "error::operator OSstream&() : error stream has failed"
				<< endl;
			abort();
		}

		return *messageStreamPtr_;
	}

	error::operator dictionary() const
	{
		dictionary errDict;

		string oneLineMessage(message());
		oneLineMessage.replaceAll('\n', ' ');

		errDict.add("type", word("tnbLib::error"));
		errDict.add("message", oneLineMessage);
		errDict.add("function", functionName());
		errDict.add("sourceFile", sourceFileName());
		errDict.add("sourceFileLineNumber", sourceFileLineNumber());

		return errDict;
	}
}


tnbLib::string tnbLib::error::message() const
{
	return messageStreamPtr_->str();
}


void tnbLib::error::exit(const int errNo)
{
	if (!throwExceptions_ && JobInfo::constructed)
	{
		jobInfo.add("FatalError", operator dictionary());
		jobInfo.exit();
	}

	if (abort_)
	{
		Perr << endl << *this << endl
			<< "\nTONB aborting (TONB_ABORT set)\n" << endl;

		abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nTONB parallel run exiting\n" << endl;
		Pstream::exit(errNo);
	}
	else
	{
		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			error errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nTONB exiting\n" << endl;
			::exit(1);
		}
	}
}


void tnbLib::error::abort()
{
	if (!throwExceptions_ && JobInfo::constructed)
	{
		jobInfo.add("FatalError", operator dictionary());
		jobInfo.abort();
	}

	if (abort_)
	{
		Perr << endl << *this << endl
			<< "\nTONB aborting (TONB_ABORT set)\n" << endl;
		printStack(Perr);
		::abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nTONB parallel run aborting\n" << endl;
		printStack(Perr);
		Pstream::abort();
	}
	else
	{
		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			error errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nTONB aborting\n" << endl;
			printStack(Perr);
			::abort();
		}
	}
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const error& fErr)
{
	os << endl
		<< fErr.title().c_str() << endl
		<< fErr.message().c_str();

	if (error::level >= 2 && fErr.sourceFileLineNumber())
	{
		os << endl << endl
			<< "    From function " << fErr.functionName().c_str() << endl
			<< "    in file " << fErr.sourceFileName().c_str()
			<< " at line " << fErr.sourceFileLineNumber() << '.';
	}

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global error definitions

tnbLib::error tnbLib::FatalError("--> TONB FATAL ERROR: ");

// ************************************************************************* //
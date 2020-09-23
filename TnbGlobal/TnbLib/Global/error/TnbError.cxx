#include <TnbError.hxx>

#include <OSspecific.hxx>
#include <OStringStream.hxx>
#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <ITstream.hxx>
#include <Pstream.hxx>
#include <JobInfo.hxx>

tnbLib::OSstream &
tnbLib::ConvError::operator()
(
	const char * functionName,
	const char * sourceFileName,
	const int sourceFileLineNumber,
	const label nbIterations,
	const scalar tolerance
	)
{
	functionName_ = functionName;
	sourceFileName_ = sourceFileName;
	sourceFileLineNumber_ = sourceFileLineNumber;

	nbIterations_ = nbIterations;
	theTolerance_ = tolerance;

	return operator OSstream&();
}

void tnbLib::ConvError::exit(const int errNo)
{
	if (!throwExceptions_ && jobInfo::constructed)
	{
		jobInfo_.add("FatalError", operator dictionary());
		jobInfo_.exit();
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
			ConvError errorException(*this);

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

void tnbLib::ConvError::abort()
{
	if (!throwExceptions_ && jobInfo::constructed)
	{
		jobInfo_.add("FatalError", operator dictionary());
		jobInfo_.abort();
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
			ConvError errorException(*this);

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

namespace tnbLib
{

	Ostream & operator<<(Ostream & os, const ConvError & fErr)
	{
		os << endl
			<< fErr.title().c_str() << endl
			<< fErr.message().c_str();

		os << "nb of Iterations: " << fErr.NbIterations() << endl;
		os << "tolerance: " << fErr.Tolerance() << endl;

		if (error::level >= 2 && fErr.sourceFileLineNumber())
		{
			os << endl << endl
				<< "    From function " << fErr.functionName().c_str() << endl
				<< "    in file " << fErr.sourceFileName().c_str()
				<< " at line " << fErr.sourceFileLineNumber() << '.';
		}

		return os;
	}
}

tnbLib::ConvError tnbLib::FatalConvError("--> TONB ITERATION FAILED:");
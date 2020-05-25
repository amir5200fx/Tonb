#pragma once
#ifndef _messageStream_Header
#define _messageStream_Header

#include <label.hxx>
#include <tnbString.hxx>
#include <debugSwitch.hxx>

namespace tnbLib
{

	class IOstream;
	class Ostream;
	class OSstream;
	class OStringStream;
	class dictionary;

	/*---------------------------------------------------------------------------*\
							   Class messageStream Declaration
	\*---------------------------------------------------------------------------*/

	class messageStream
	{

	public:

		//- Severity flags
		enum errorSeverity
		{
			INFO,       // Debugging information in event of error
			WARNING,    // Warning of possible problem
			SERIOUS,    // A serious problem (data corruption?)
			FATAL       // Oh bugger!
		};


	protected:

		// Private data

		string title_;
		errorSeverity severity_;
		int maxErrors_;
		int errorCount_;


	public:

		// Debug switches

		static debug::debugSwitch level;


		// Constructors

			//- Construct from components
		messageStream
		(
			const string& title,
			errorSeverity sev,
			const int maxErrors = 0
		);


		//- Construct from dictionary
		messageStream(const dictionary& dict);


		// Member functions

			//- Return the title of this error type
		const string& title() const
		{
			return title_;
		}

		//- Return the maximum number of errors before program termination
		int maxErrors() const
		{
			return maxErrors_;
		}

		//- Return non-const access to the maximum number of errors before
		//  program termination to enable user to reset it
		int& maxErrors()
		{
			return maxErrors_;
		}

		//- Convert to Ostream
		//  Prints basic message and then returns Ostream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		OSstream& operator()
			(
				const string& functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber = 0
				);

		//- Convert to Ostream
		//  Prints basic message and then returns Ostream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const string& ioFileName,
				const label ioStartLineNumber = -1,
				const label ioEndLineNumber = -1
				);

		//- Convert to Ostream
		//  Prints basic message and then returns Ostream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const IOstream&
				);

		//- Convert to Ostream
		//  Prints basic message and then returns Ostream for further info.
		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const dictionary&
				);

		//- Convert to Ostream for << operations
		operator OSstream&();

		//- Explicitly convert to Ostream for << operations
		OSstream& operator()()
		{
			return operator OSstream&();
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Global error declarations: defined in messageStream.C

	extern messageStream SeriousError;
	extern messageStream Warning;
	extern messageStream Info;
	extern bool writeInfoHeader;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Convenient macros to add the file name and line number to the function name

//#define SeriousErrorIn(fn) SeriousError(fn, __FILE__, __LINE__)
//#define SeriousIOErrorIn(fn, ios) SeriousError(fn, __FILE__, __LINE__, ios)
//
//#define WarningIn(fn) Warning(fn, __FILE__, __LINE__)
//#define IOWarningIn(fn, ios) Warning(fn, __FILE__, __LINE__, ios)
//
//#define InfoIn(fn) Info(fn, __FILE__, __LINE__)
//#define IOInfoIn(fn, ios) Info(fn, __FILE__, __LINE__, ios)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

// Compiler provided function name string:
//     for gcc-compatible compilers use __PRETTY_FUNCTION__
//     otherwise use the standard __func__
#ifdef __GNUC__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define FUNCTION_NAME __func__
#endif


//- Report an error message using tnbLib::SeriousError
//  for functionName in file __FILE__ at line __LINE__
#define SeriousErrorIn(functionName)                                           \
    ::tnbLib::SeriousError((functionName), __FILE__, __LINE__)

//- Report an error message using tnbLib::SeriousError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define SeriousErrorInFunction SeriousErrorIn(FUNCTION_NAME)


//- Report an IO error message using tnbLib::SeriousError
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SeriousIOErrorIn(functionName, ios)                                    \
    ::tnbLib::SeriousError((functionName), __FILE__, __LINE__, ios)

//- Report an IO error message using tnbLib::SeriousError
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define SeriousIOErrorInFunction(ios) SeriousIOErrorIn(FUNCTION_NAME, ios)


//- Report a warning using tnbLib::Warning
//  for functionName in file __FILE__ at line __LINE__
#define WarningIn(functionName)                                                \
    ::tnbLib::Warning((functionName), __FILE__, __LINE__)

//- Report a warning using tnbLib::Warning
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define WarningInFunction WarningIn(FUNCTION_NAME)


//- Report an IO warning using tnbLib::Warning
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOWarningIn(functionName, ios)                                         \
    ::tnbLib::Warning((functionName), __FILE__, __LINE__, (ios))

//- Report an IO warning using tnbLib::Warning
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOWarningInFunction(ios) IOWarningIn(FUNCTION_NAME, ios)


//- Report an information message using tnbLib::Info
//  for functionName in file __FILE__ at line __LINE__
#define InfoIn(functionName)                                                   \
    ::tnbLib::Info((functionName), __FILE__, __LINE__)

//- Report an information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
#define InfoInFunction InfoIn(FUNCTION_NAME)

//- Report write to tnbLib::Info if the local log switch is true
#define InfoHeader                                                             \
    if (::tnbLib::writeInfoHeader) Info

//- Report write to tnbLib::Info if the local log switch is true
#define Log                                                                    \
    if (log) Info


//- Report an IO information message using tnbLib::Info
//  for functionName in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOInfoIn(functionName, ios)                                            \
    ::tnbLib::Info((functionName), __FILE__, __LINE__, (ios))

//- Report an IO information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  for a particular IOstream
#define IOInfoInFunction(ios) IOInfoIn(FUNCTION_NAME, ios)


//- Report an information message using tnbLib::Info
//  if the local debug switch is true
#define tnbDebugInfo                                                              \
    if (debug) Info

//- Report an information message using tnbLib::Info
//  for FUNCTION_NAME in file __FILE__ at line __LINE__
//  if the local debug switch is true
#define DebugInFunction                                                        \
    if (debug) InfoInFunction

//- Report a variable name and value
//  using tnbLib::Pout in file __FILE__ at line __LINE__
#define DebugVar(var)                                                          \
{                                                                              \
    ::tnbLib::string oldPrefix(::tnbLib::Pout.prefix());                           \
    ::tnbLib::Pout<< "["<< __FILE__ << ":" << __LINE__ << "] ";                  \
    ::tnbLib::Pout.prefix() = oldPrefix + #var " ";                              \
    ::tnbLib::Pout<< var << ::tnbLib::endl;                                        \
    ::tnbLib::Pout.prefix() = oldPrefix;                                         \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_messageStream_Header

#pragma once
#ifndef _TnbError_Header
#define _TnbError_Header

#include <error.hxx>
#include <Global_Module.hxx>

namespace tnbLib
{

	class ConvError
		: public error
	{

		/*Private Data*/

		label nbIterations_;
		scalar theTolerance_;

	public:

		ConvError(const string& title)
			: error(title)
		{}

		virtual ~ConvError() throw()
		{}

		label NbIterations() const
		{
			return nbIterations_;
		}

		scalar Tolerance() const
		{
			return theTolerance_;
		}

		void SetNbIterations(const label value)
		{
			nbIterations_ = value;
		}

		void SetTolerance(const scalar value)
		{
			theTolerance_ = value;
		}

		TnbGlobal_EXPORT OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const label nbIterations,
				const scalar tolerance
				);

		//- Exit : can be called for any error to exit program
		TnbGlobal_EXPORT void exit(const int errNo = 1);

		//- Abort : used to stop code for fatal errors
		TnbGlobal_EXPORT void abort();


		// Ostream operator

		friend TnbGlobal_EXPORT Ostream& operator<<(Ostream&, const ConvError&);
	};

	extern TnbGlobal_EXPORT ConvError FatalConvError;

#define FatalConvErrorIn(fn, nbIters, tol) FatalConvError(fn, __FILE__, __LINE__, nbIters, tol)
}

#include <TnbErrorM.hxx>

#endif // !_TnbError_Header

#pragma once
#ifndef _TnbErrorManip_Header
#define _TnbErrorManip_Header

#include <TnbError.hxx>

namespace tnbLib
{

	inline errorManipArg<ConvError, int>
		exit(ConvError& err, const int errNo = 1)
	{
		return errorManipArg<ConvError, int>(&ConvError::exit, err, errNo);
	}

	inline errorManip<ConvError>
		abort(ConvError& err)
	{
		return errorManip<ConvError>(&ConvError::abort, err);
	}
}

#endif // !_TnbErrorManip_Header

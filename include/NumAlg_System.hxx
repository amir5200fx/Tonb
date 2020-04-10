#pragma once
#ifndef _NumAlg_System_Header
#define _NumAlg_System_Header

#include <Standard_TypeDef.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	namespace sysLib
	{

		void init_TnbNumAlg();
	}

	namespace Iter
	{
		void inline ChackFun(const char* funcName)
		{
			FatalErrorIn(funcName)
				<< " Found no function"
				<< abort(FatalError);
		}

		template<bool Cond = true>
		void inline CheckBound
		(
			Standard_Real& x,
			const Standard_Real theLower,
			const Standard_Real theUpper
		)
		{
			if (x < theLower) x = theLower;
			if (x > theUpper) x = theUpper;
		}

		template<>
		void inline CheckBound<false>
			(
				Standard_Real& x,
				const Standard_Real theLower,
				const Standard_Real theUpper
				)
		{}
	}
}

#endif // !_NumAlg_System_Header

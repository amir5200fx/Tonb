#pragma once
#ifndef _StbGMaker_Hull_Header
#define _StbGMaker_Hull_Header

#include <StbGMaker_Volume.hxx>

namespace tnbLib
{

	class StbGMaker_Hull
		: public StbGMaker_Volume
	{

		/*Private Data*/

	public:

		template<class... _Types>
		StbGMaker_Hull(const _Types&&... _Args)
			: StbGMaker_Volume(_Args...)
		{}

		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_StbGMaker_Hull_Header

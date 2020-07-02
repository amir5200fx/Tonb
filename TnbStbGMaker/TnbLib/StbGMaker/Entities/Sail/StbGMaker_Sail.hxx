#pragma once
#ifndef _StbGMaker_Sail_Header
#define _StbGMaker_Sail_Header

#include <StbGMaker_Volume.hxx>

namespace tnbLib
{

	class StbGMaker_Sail
		: public StbGMaker_Volume
	{

		/*Private Data*/

	public:

		template<class... _Types>
		StbGMaker_Sail(const _Types&&... _Args)
			: StbGMaker_Volume(_Args...)
		{}

		Standard_Boolean IsSail() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_StbGMaker_Sail_Header

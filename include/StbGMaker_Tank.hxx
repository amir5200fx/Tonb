#pragma once
#ifndef _StbGMaker_Tank_Header
#define _StbGMaker_Tank_Header

#include <StbGMaker_Volume.hxx>

namespace tnbLib
{

	class StbGMaker_Tank
		: public StbGMaker_Volume
	{

		/*Private Data*/

	public:

		template<class... _Types>
		StbGMaker_Tank(const _Types&&... _Args)
			: StbGMaker_Volume(_Args...)
		{}

		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_StbGMaker_Tank_Header

#pragma once
#ifndef _Voyage_LongMap_Header
#define _Voyage_LongMap_Header

#include <Pnt2d.hxx>

namespace tnbLib
{

	class Voyage_LongMap
	{

		/*Private Data*/

	public:

		// Public functions and operators [7/9/2023 Payvand]

		Standard_Real CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1) const;

	};

}

#endif // !_Voyage_LongMap_Header

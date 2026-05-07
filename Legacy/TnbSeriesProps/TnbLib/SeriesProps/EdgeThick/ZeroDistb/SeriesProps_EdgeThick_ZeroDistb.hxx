#pragma once
#ifndef _SeriesProps_EdgeThick_ZeroDistb_Header
#define _SeriesProps_EdgeThick_ZeroDistb_Header

#include <SeriesProps_EdgeThick.hxx>

namespace tnbLib
{

	class SeriesProps_EdgeThick_ZeroDistb
		: public SeriesProps_EdgeThick
	{

		/*Private Data*/

	public:

		// default constructor [12/31/2022 Payvand]

		SeriesProps_EdgeThick_ZeroDistb()
		{}


		// constructors [12/31/2022 Payvand]


		// Public functions and operators [12/31/2022 Payvand]

		Standard_Real Value(const Standard_Real rPerR) const
		{
			return 0.0;
		}
	};
}

#endif // !_SeriesProps_EdgeThick_ZeroDistb_Header

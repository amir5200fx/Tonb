#pragma once
#ifndef _SeriesProps_EdgeThick_Header
#define _SeriesProps_EdgeThick_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class SeriesProps_EdgeThick
	{

		/*Private Data*/

	protected:

		// default constructor [12/31/2022 Payvand]

		SeriesProps_EdgeThick()
		{}


		// constructors [12/31/2022 Payvand]


	public:


		// Public functions and operators [12/31/2022 Payvand]

		virtual Standard_Real Value(const Standard_Real rPerR) const = 0;

	};
}

#endif // !_SeriesProps_EdgeThick_Header

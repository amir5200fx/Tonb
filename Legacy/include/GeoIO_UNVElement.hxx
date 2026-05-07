#pragma once
#ifndef _GeoIO_UNVElement_Header
#define _GeoIO_UNVElement_Header

#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class GeoIO_UNVElement
	{

		/*Private Data*/

		std::vector<Standard_Integer> theIdes_;

	protected:

		// default constructor [9/4/2023 aamir]

		GeoIO_UNVElement()
		{}

		// constructors [9/4/2023 aamir]

	public:

		// Public functions and operators [9/4/2023 aamir]

		const auto& Ids() const { return theIdes_; }

	};
}

#endif // !_GeoIO_UNVElement_Header

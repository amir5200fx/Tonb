#pragma once
#ifndef _GeoIO_UNVPoint_Header
#define _GeoIO_UNVPoint_Header

#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class GeoIO_UNVPoint
	{

		/*Private Data*/

	protected:

		// default constructor [9/4/2023 aamir]

		GeoIO_UNVPoint()
		{}

		// constructors [9/4/2023 aamir]

	public:

		enum dim
		{
			two = 2,
			three
		};

		// Public functions and operators [9/4/2023 aamir]

		virtual std::vector<Standard_Real> Components() const = 0;
		virtual dim Dimension() const = 0;

	};
}

#endif // !_GeoIO_UNVPoint_Header

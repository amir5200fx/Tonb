#pragma once
#ifndef _VoyageField_Wind_Header
#define _VoyageField_Wind_Header

#include <Voyage_Wind.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageField_Wind
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageField_Wind()
		{}

		// constructors [7/11/2023 Payvand]

	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual std::shared_ptr<Voyage_Wind> Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageField_Wind_Header

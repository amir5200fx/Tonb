#pragma once
#ifndef _VoyageField_Earth_Header
#define _VoyageField_Earth_Header

#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageField_Earth
	{

		/*Private Data*/

	public:

		// default constructor [7/20/2023 Payvand]

		VoyageField_Earth()
		{}

		// constructors [7/20/2023 Payvand]


		// Public functions and operators [7/20/2023 Payvand]

		Standard_Boolean IsValid(const Pnt2d&) const;

	};
}

#endif // !_VoyageField_Earth_Header

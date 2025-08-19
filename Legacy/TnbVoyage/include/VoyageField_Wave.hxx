#pragma once
#ifndef _VoyageField_Wave_Header
#define _VoyageField_Wave_Header

#include <Voyage_Wave.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageField_Wave
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageField_Wave()
		{}

		// constructors [7/11/2023 Payvand]


	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual std::shared_ptr<Voyage_Wave> Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageField_Wave_Header

#pragma once
#ifndef _VoyageField_Current_Header
#define _VoyageField_Current_Header

#include <Voyage_Current.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageField_Current
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageField_Current()
		{}

		// constructors [7/11/2023 Payvand]

	public:

		virtual std::shared_ptr<Voyage_Current> Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageField_Current_Header

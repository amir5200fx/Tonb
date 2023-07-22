#pragma once
#ifndef _Voyage_Profile_Header
#define _Voyage_Profile_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Voyage_Profile
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		Voyage_Profile()
		{}

		// constructors [7/11/2023 Payvand]


	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual Standard_Real X0() const = 0;
		virtual Standard_Real X1() const = 0;

		inline Standard_Real Value0() const;
		inline Standard_Real Value1() const;

		virtual Standard_Real Value(const Standard_Real x) const = 0;

	};
}

#include <Voyage_ProfileI.hxx>

#endif // !_Voyage_Profile_Header

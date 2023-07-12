#pragma once
#ifndef _VoyageFun_Resistance_Header
#define _VoyageFun_Resistance_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class VoyageFun_Resistance
	{

		/*Private Data*/

	protected:

		// default constructor [7/10/2023 Payvand]

		VoyageFun_Resistance()
		{}

		// constructors [7/10/2023 Payvand]

	public:

		// Public functions and operators [7/10/2023 Payvand]

		virtual Standard_Real Value(const Standard_Real theVelocity) const = 0;

	};
}

#endif // !_VoyageFun_Resistance_Header

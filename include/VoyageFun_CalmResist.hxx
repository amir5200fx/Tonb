#pragma once
#ifndef _VoyageFun_CalmResist_Header
#define _VoyageFun_CalmResist_Header

#include <VoyageFun_Resistance.hxx>

namespace tnbLib
{

	class VoyageFun_CalmResist
		: public VoyageFun_Resistance
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageFun_CalmResist()
		{}

	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual Standard_Real Value(const Standard_Real theVel) const = 0;

	};

}

#endif // !_VoyageFun_CalmResist_Header

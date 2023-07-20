#pragma once
#ifndef _VoyageFun_CostFunction_Header
#define _VoyageFun_CostFunction_Header

#include <Pnt2d.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class VoyageFun_CostFunction
	{

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageFun_CostFunction()
		{}

		// constructors [7/11/2023 Payvand]


	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual Standard_Real Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageFun_CostFunction_Header

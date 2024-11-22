#pragma once
#ifndef _VoyageFun_CostFunction_Header
#define _VoyageFun_CostFunction_Header

#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]

	class VoyageFun_CostFunction
	{

	public:
		
		struct Time
		{
			Standard_Real value;
		};

		struct State
		{
			Pnt2d pos;
			Time time;
		};

	private:

		/*Private Data*/

	protected:

		// default constructor [7/11/2023 Payvand]

		VoyageFun_CostFunction()
		{}

		// constructors [7/11/2023 Payvand]


	public:

		// Public functions and operators [7/11/2023 Payvand]

		virtual Standard_Real Value(const State& theState0, const State& theState1) const = 0;

	};

}

#endif // !_VoyageFun_CostFunction_Header

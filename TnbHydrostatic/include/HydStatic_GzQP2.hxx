#pragma once
#ifndef _HydStatic_GzQP2_Header
#define _HydStatic_GzQP2_Header

#include <HydStatic_GzQ.hxx>

namespace tnbLib
{

	class HydStatic_GzQP2
		: public HydStatic_GzQ
	{

		/*Private Data*/

		Standard_Real theParameter0_;
		Standard_Real theParameter1_;

	public:

		HydStatic_GzQP2()
		{}

		HydStatic_GzQP2
		(
			const Standard_Real theHeel,
			const Standard_Real theArm, 
			const Standard_Real theParam0,
			const Standard_Real theParam1
		)
			: HydStatic_GzQ(theHeel, theArm)
			, theParameter0_(theParam0)
			, theParameter1_(theParam1)
		{}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter0)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter1)
	};
}

#endif // !_HydStatic_GzQP2_Header

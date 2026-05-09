#pragma once
#ifndef _HydStatic_StEqQ_Header
#define _HydStatic_StEqQ_Header

#include <HydStatic_EqQ.hxx>

namespace tnbLib
{

	class HydStatic_StEqQ
		: public HydStatic_EqQ
	{

		/*Private Data*/

	public:

		static TnbHydStatic_EXPORT const HydStatic_EqQ null;

		HydStatic_StEqQ()
		{}

		HydStatic_StEqQ
		(
			const Standard_Real theHeel,
			const Standard_Real theArm,
			const Standard_Real theParam0,
			const Standard_Real theParam1
		)
			: HydStatic_EqQ(theHeel, theArm, theParam0, theParam1)
		{}


		Standard_Boolean IsStable() const override
		{
			return Standard_True;
		}

	};
}

#endif // !_HydStatic_StEqQ_Header

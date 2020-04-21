#pragma once
#ifndef _HydStatic_UnEqQ_Header
#define _HydStatic_UnEqQ_Header

#include <HydStatic_EqQ.hxx>

namespace tnbLib
{

	class HydStatic_UnEqQ
		: public HydStatic_EqQ
	{

		/*Private Data*/

	public:

		HydStatic_UnEqQ()
		{}

		HydStatic_UnEqQ
		(
			const Standard_Real theHeel,
			const Standard_Real theArm,
			const Standard_Real theParam0,
			const Standard_Real theParam1
		)
			: HydStatic_EqQ(theHeel, theArm, theParam0, theParam1)
		{}


		Standard_Boolean IsUnStable() const override
		{
			return Standard_True;
		}

	};
}

#endif // !_HydStatic_UnEqQ_Header

#pragma once
#ifndef _HydStatic_EqQ_Header
#define _HydStatic_EqQ_Header

#include <HydStatic_GzQP2.hxx>

namespace tnbLib
{

	class HydStatic_EqQ
		: public HydStatic_GzQP2
	{

		/*Private Data*/

	protected:

		HydStatic_EqQ()
		{}

		HydStatic_EqQ
		(
			const Standard_Real theHeel,
			const Standard_Real theArm,
			const Standard_Real theParam0,
			const Standard_Real theParam1
		)
			: HydStatic_GzQP2(theHeel, theArm, theParam0, theParam1)
		{}

	public:

		static const HydStatic_EqQ null;

		virtual Standard_Boolean IsStable() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsUnStable() const
		{
			return Standard_False;
		}

		static Standard_Boolean IsNull(const HydStatic_EqQ& theQ);
	};
}

#endif // !_HydStatic_EqQ_Header

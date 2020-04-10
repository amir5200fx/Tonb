#pragma once
#ifndef _HydStatic_LeverArmPair_Header
#define _HydStatic_LeverArmPair_Header

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class HydStatic_LeverArmPair
	{

		/*Private Data*/

		Standard_Real theHeel_;
		Standard_Real theLeverArm_;

	public:

		HydStatic_LeverArmPair
		(
			const Standard_Real theHeel, 
			const Standard_Real theLeverArm
		)
			: theHeel_(theHeel)
			, theLeverArm_(theLeverArm)
		{
		}

		auto Heel() const
		{
			return theHeel_;
		}

		auto LeverArm() const
		{
			return theLeverArm_;
		}
	};
}

#endif // !_HydStatic_LeverArmPair_Header

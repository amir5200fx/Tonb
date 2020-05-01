#pragma once
#ifndef _HydStatic_StbFun_rArm_Header
#define _HydStatic_StbFun_rArm_Header

#include <HydStatic_StbFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_rArmCurve;

	namespace hydStcLib
	{

		class StbFun_rArm
			: public HydStatic_StbFun
		{

			/*Private Data*/

			std::shared_ptr<HydStatic_rArmCurve> theArm_;

		public:

			StbFun_rArm
			(
				const std::shared_ptr<HydStatic_rArmCurve>& theArm
			)
				: theArm_(theArm)
			{}

			StbFun_rArm
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<HydStatic_rArmCurve>& theArm
			)
				: HydStatic_StbFun(theIndex)
				, theArm_(theArm)
			{}

			StbFun_rArm
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<HydStatic_rArmCurve>& theArm
			)
				: HydStatic_StbFun(theIndex, theName)
				, theArm_(theArm)
			{}


			Standard_Boolean IsRighting() const override
			{
				return Standard_True;
			}

			Standard_Real MinHeel() const override;

			Standard_Real MaxHeel() const override;

			Standard_Real Value(const Standard_Real thePhi) const override;

			const auto& Arm() const
			{
				return theArm_;
			}
		};
	}
}

#endif // !_HydStatic_StbFun_rArm_Header

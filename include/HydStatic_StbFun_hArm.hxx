#pragma once
#ifndef _HydStatic_StbFun_hArm_Header
#define _HydStatic_StbFun_hArm_Header

#include <HydStatic_StbFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_hArmCurve;

	namespace hydStcLib
	{

		class StbFun_hArm
			: public HydStatic_StbFun
		{

			/*Private Data*/

			std::shared_ptr<HydStatic_hArmCurve> theArm_;

		public:

			StbFun_hArm
			(
				const std::shared_ptr<HydStatic_hArmCurve>&& theArm
			)
				: theArm_(std::move(theArm))
			{}

			StbFun_hArm
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<HydStatic_hArmCurve>&& theArm
			)
				: HydStatic_StbFun(theIndex)
				, theArm_(std::move(theArm))
			{}

			StbFun_hArm
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<HydStatic_hArmCurve>&& theArm
			)
				: HydStatic_StbFun(theIndex, theName)
				, theArm_(std::move(theArm))
			{}


			Standard_Boolean IsHeeling() const override
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

#endif // !_HydStatic_StbFun_hArm_Header

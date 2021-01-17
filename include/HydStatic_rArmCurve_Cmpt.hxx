#pragma once
#ifndef _HydStatic_rArmCurve_Cmpt_Header
#define _HydStatic_rArmCurve_Cmpt_Header

#include <HydStatic_Entity.hxx>

#include <vector>

namespace tnbLib
{

	namespace hydStcLib
	{

		template<class ArmCurve>
		class rArmCurve_Cmpt
			: public HydStatic_Entity
		{

			/*Private Data*/

			std::vector<std::shared_ptr<ArmCurve>> theCurves_;

		public:

			rArmCurve_Cmpt()
			{}

			rArmCurve_Cmpt
			(
				const std::vector<std::shared_ptr<ArmCurve>>&& theCurves
			)
				: theCurves_(std::move(theCurves))
			{}

			rArmCurve_Cmpt
			(
				const Standard_Integer theIndex
			)
				: HydStatic_Entity(theIndex)
			{}

			rArmCurve_Cmpt
			(
				const Standard_Integer theIndex, 
				const word& theName
			)
				: HydStatic_Entity(theIndex, theName)
			{}

			auto NbCurves() const
			{
				return (Standard_Integer)theCurves_.size();
			}

			const auto& Curves() const
			{
				return theCurves_;
			}

			auto& ChangeCurves() 
			{
				return theCurves_;
			}

			void SetCurves
			(
				const std::vector<std::shared_ptr<ArmCurve>>&& theCurves
			)
			{
				theCurves_ = std::move(theCurves);
			}
		};
	}
}

#endif // !_HydStatic_rArmCurve_Cmpt_Header

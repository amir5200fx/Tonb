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


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				//- this function should never be called
				NotImplemented;
			}

		public:

			rArmCurve_Cmpt()
			{}

			rArmCurve_Cmpt
			(
				const Standard_Integer theIndex,
				const word& theName
			)
				: HydStatic_Entity(theIndex, theName)
			{}

			rArmCurve_Cmpt
			(
				const std::vector<std::shared_ptr<ArmCurve>>& theCurves
			)
				: theCurves_(theCurves)
			{}

			rArmCurve_Cmpt
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::vector<std::shared_ptr<ArmCurve>>& theCurves
			)
				: HydStatic_Entity(theIndex, theName)
				, theCurves_(theCurves)
			{}

			rArmCurve_Cmpt
			(
				std::vector<std::shared_ptr<ArmCurve>>&& theCurves
			)
				: theCurves_(std::move(theCurves))
			{}

			rArmCurve_Cmpt
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<std::shared_ptr<ArmCurve>>&& theCurves
			)
				: HydStatic_Entity(theIndex, theName)
				, theCurves_(std::move(theCurves))
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
				std::vector<std::shared_ptr<ArmCurve>>&& theCurves
			)
			{
				theCurves_ = std::move(theCurves);
			}

			void SetCurves
			(
				const std::vector<std::shared_ptr<ArmCurve>>& theCurves
			)
			{
				theCurves_ = theCurves;
			}
		};
	}
}

#endif // !_HydStatic_rArmCurve_Cmpt_Header

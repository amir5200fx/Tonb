#pragma once
#ifndef _Cad2d_CurveLength_Adaptive_Info_Header
#define _Cad2d_CurveLength_Adaptive_Info_Header

#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/6/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	namespace cad2dLib
	{

		class CurveLength_Adaptive_Info
		{

			/*Private Data*/

			std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

			Standard_Integer theMaxLevel_;


			// private functions and operators [2/6/2022 Amir]

			TNB_SERIALIZATION(TnbCad2d_EXPORT);

		public:

			static TnbCad2d_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;
			static TnbCad2d_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;

			// default constructor [2/6/2022 Amir]

			CurveLength_Adaptive_Info()
			{}

			// constructors [2/6/2022 Amir]

			CurveLength_Adaptive_Info
			(
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo,
				const Standard_Integer theMaxLevel
			)
				: theIntegInfo_(theInfo)
				, theMaxLevel_(theMaxLevel)
			{}

			CurveLength_Adaptive_Info
			(
				std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo,
				const Standard_Integer theMaxLevel
			)
				: theIntegInfo_(std::move(theInfo))
				, theMaxLevel_(theMaxLevel)
			{}

			// public functions and operators [2/6/2022 Amir]

			auto MaxLevel() const
			{
				return theMaxLevel_;
			}

			const auto& IntegInfo() const
			{
				return theIntegInfo_;
			}

			void SetMaxLevel(const Standard_Integer theMaxLev)
			{
				theMaxLevel_ = theMaxLev;
			}

			void SetIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
			{
				theIntegInfo_ = theInfo;
			}

			void SetIntegInfo(std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo)
			{
				theIntegInfo_ = std::move(theInfo);
			}
		};
	}
}

#endif // !_Cad2d_CurveLength_Adaptive_Info_Header

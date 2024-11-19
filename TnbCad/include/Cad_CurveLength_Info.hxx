#pragma once
#ifndef _Cad_CurveLength_Info_Header
#define _Cad_CurveLength_Info_Header

#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/17/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad_CurveLength_Info
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

		Standard_Integer theMaxLevel_;


		// private functions and operators [1/21/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;

		// default constructor [1/17/2022 Amir]

		Cad_CurveLength_Info()
			: theIntegInfo_(DEFAULT_INTEG_INFO)
			, theMaxLevel_(DEFAULT_MAX_LEVEL)
		{}

		// constructors [1/17/2022 Amir]

		Cad_CurveLength_Info
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theIntegInfo, 
			const Standard_Integer theMaxLevel
		)
			: theIntegInfo_(theIntegInfo)
			, theMaxLevel_(theMaxLevel)
		{}

		Cad_CurveLength_Info
		(
			std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theIntegInfo,
			const Standard_Integer theMaxLevel
		)
			: theIntegInfo_(std::move(theIntegInfo))
			, theMaxLevel_(theMaxLevel)
		{}


		// public functions and operators [1/17/2022 Amir]

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

#endif // !_Cad_CurveLength_Info_Header

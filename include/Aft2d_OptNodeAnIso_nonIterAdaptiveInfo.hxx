#pragma once
#ifndef _Aft2d_OptNodeAnIso_nonIterAdaptiveInfo_Header
#define _Aft2d_OptNodeAnIso_nonIterAdaptiveInfo_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [3/5/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;
	class Aft_SizeCorr_FractionInfo;

	class Aft2d_OptNodeAnIso_nonIterAdaptiveInfo
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theCalculatorInfo_;
		std::shared_ptr<Aft_SizeCorr_FractionInfo> theCorrectorInfo_;


		// private functions and operators [3/6/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::string extension;

		static TnbMesh_EXPORT const std::shared_ptr<Aft_SizeCorr_IterativeInfo> DEFAULT_CALCULATOR_INFO;
		static TnbMesh_EXPORT const std::shared_ptr<Aft_SizeCorr_FractionInfo> DEFAULT_CORRECTOR_INFO;

		// default constructor [3/5/2022 Amir]

		Aft2d_OptNodeAnIso_nonIterAdaptiveInfo()
			: theCalculatorInfo_(DEFAULT_CALCULATOR_INFO)
			, theCorrectorInfo_(DEFAULT_CORRECTOR_INFO)
		{}


		// constructors [3/5/2022 Amir]

		Aft2d_OptNodeAnIso_nonIterAdaptiveInfo
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theCalculator,
			const std::shared_ptr<Aft_SizeCorr_FractionInfo>& theCorrector
		)
			: theCalculatorInfo_(theCalculator)
			, theCorrectorInfo_(theCorrector)
		{}

		Aft2d_OptNodeAnIso_nonIterAdaptiveInfo
		(
			std::shared_ptr<Aft_SizeCorr_IterativeInfo>&& theCalculator,
			std::shared_ptr<Aft_SizeCorr_FractionInfo>&& theCorrector
		)
			: theCalculatorInfo_(std::move(theCalculator))
			, theCorrectorInfo_(std::move(theCorrector))
		{}

		// public functions and operators [3/5/2022 Amir]

		const auto& CalculatorInfo() const
		{
			return theCalculatorInfo_;
		}

		const auto& CorrectorInfo() const
		{
			return theCorrectorInfo_;
		}

		void SetCalculatorInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo)
		{
			theCalculatorInfo_ = theInfo;
		}

		void SetCorrectorInfo(const std::shared_ptr<Aft_SizeCorr_FractionInfo>& theInfo)
		{
			theCorrectorInfo_ = theInfo;
		}

		void SetCalculatorInfo(std::shared_ptr<Aft_SizeCorr_IterativeInfo>&& theInfo)
		{
			theCalculatorInfo_ = std::move(theInfo);
		}

		void SetCorrectorInfo(std::shared_ptr<Aft_SizeCorr_FractionInfo>&& theInfo)
		{
			theCorrectorInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Aft2d_OptNodeAnIso_nonIterAdaptiveInfo_Header

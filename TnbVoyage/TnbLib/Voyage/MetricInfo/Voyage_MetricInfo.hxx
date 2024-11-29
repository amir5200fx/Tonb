#pragma once
#ifndef _Voyage_MetricInfo_Header
#define _Voyage_MetricInfo_Header

#include <Voyage_Module.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/26/2023 aamir]
	class Mesh_Curve_Info;
	class Aft_SizeCorr_IterativeInfo;
	class Aft_MetricPrcsrAnIso_Info;
	class NumAlg_AdaptiveInteg_Info;
	class NumAlg_NelderMeadInfo;

	class Voyage_MetricInfo
	{

		/*Private Data*/

		std::shared_ptr<Mesh_Curve_Info> theCurveMeshInfo_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theMetricInfo_;
		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theSizeCorrIterInfo_;
		std::shared_ptr<NumAlg_NelderMeadInfo> theNelderInfo_;

		Standard_Integer theNbSamples_;
		Standard_Integer theMaxSubdivideLev_;

		Standard_Integer theMaxSubTriSubdivideLev_;

		Standard_Integer theNbMetricIters_;

		Standard_Real theMetricTol_;

	public:

		static TnbVoyage_EXPORT std::shared_ptr<Mesh_Curve_Info> DEFAULT_CURV_INFO;
		static TnbVoyage_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;
		static TnbVoyage_EXPORT std::shared_ptr<Aft_SizeCorr_IterativeInfo> DEFAULT_SIZE_CORR_ITER_INFO;
		static TnbVoyage_EXPORT std::shared_ptr<NumAlg_NelderMeadInfo> DEFAULT_NELDER_MEAD_INFO;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_MAX_SUBDIVIDE_LEVEL;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_MAX_SUBTRI_SUBDIVIDE_LEVEL;

		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_METRICS_ITERS;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_METRIC_TOL;

		// default constructor [8/26/2023 Payvand]

		Voyage_MetricInfo()
			: theCurveMeshInfo_(DEFAULT_CURV_INFO)
			, theMetricInfo_(DEFAULT_INTEG_INFO)

			, theSizeCorrIterInfo_(DEFAULT_SIZE_CORR_ITER_INFO)
			, theNelderInfo_(DEFAULT_NELDER_MEAD_INFO)

			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theMaxSubdivideLev_(DEFAULT_MAX_SUBDIVIDE_LEVEL)
			, theMaxSubTriSubdivideLev_(DEFAULT_MAX_SUBTRI_SUBDIVIDE_LEVEL)

			, theNbMetricIters_(DEFAULT_NB_METRICS_ITERS)
			, theMetricTol_(DEFAULT_METRIC_TOL)
		{}

		// constructors [8/26/2023 Payvand]

		// Public functions and operators [8/26/2023 Payvand]

		const auto& CurveMeshInfo() const { return theCurveMeshInfo_; }
		const auto& MetricInfo() const { return theMetricInfo_; }
		const auto& SizeCorrIterInfo() const { return theSizeCorrIterInfo_; }
		const auto& NelderMeadInfo() const { return theNelderInfo_; }

		auto NbSamples() const { return theNbSamples_; }
		auto MaxSubdivideLev() const { return theMaxSubdivideLev_; }
		auto MaxSubTriSubdivideLev() const { return theMaxSubTriSubdivideLev_; }

		auto NbMetricIters() const { return theNbMetricIters_; }
		auto MetricTol() const { return theMetricTol_; }

		TnbVoyage_EXPORT std::shared_ptr<Aft_MetricPrcsrAnIso_Info> CreateMetricInfo() const;

		void SetNbSamples(const Standard_Integer theNbSamples) { theNbSamples_ = theNbSamples; }
		void SetMaxSubdivideLev(const Standard_Integer theMaxLev) { theMaxSubdivideLev_ = theMaxLev; }
		void SetMaxSubTriSubdivideLev(const Standard_Integer theMaxLev) { theMaxSubTriSubdivideLev_ = theMaxLev; }

		void SetNbMetricIters(const Standard_Integer theNbIters) { theNbMetricIters_ = theNbIters; }
		void SetMetricTolerance(const Standard_Real theTol) { theMetricTol_ = theTol; }

		void OverrideCurveMeshInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveMeshInfo_ = theInfo; }
		void OverrideMetricInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo) { theMetricInfo_ = theInfo; }

		void OverrideSizeCorrIterInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo) { theSizeCorrIterInfo_ = theInfo; }
		void OverrideNelderMeadInfo(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo) { theNelderInfo_ = theInfo; }

	};
}

#endif // !_Voyage_MetricInfo_Header

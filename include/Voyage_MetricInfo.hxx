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
	class NumAlg_AdaptiveInteg_Info;

	class Voyage_MetricInfo
	{

		/*Private Data*/

		std::shared_ptr<Mesh_Curve_Info> theCurveMeshInfo_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theMetricInfo_;

		Standard_Integer theNbSamples_;
		Standard_Integer theMaxSubdivideLevs_;

	public:

		static TnbVoyage_EXPORT std::shared_ptr<Mesh_Curve_Info> DEFAULT_CURV_INFO;
		static TnbVoyage_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_MAX_SUBDIVIDE_LEVELS;

		// default constructor [8/26/2023 Payvand]

		Voyage_MetricInfo()
			: theCurveMeshInfo_(DEFAULT_CURV_INFO)
			, theMetricInfo_(DEFAULT_INTEG_INFO)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theMaxSubdivideLevs_(DEFAULT_MAX_SUBDIVIDE_LEVELS)
		{}

		// constructors [8/26/2023 Payvand]

		// Public functions and operators [8/26/2023 Payvand]

		const auto& CurveMeshInfo() const { return theCurveMeshInfo_; }
		const auto& MetricInfo() const { return theMetricInfo_; }

		auto NbSamples() const { return theNbSamples_; }
		auto MaxSubdivideLevs() const { return theMaxSubdivideLevs_; }

		void SetNbSamples(const Standard_Integer theNbSamples) { theNbSamples_ = theNbSamples; }
		void SetMaxSubdivideLevs(const Standard_Integer theMaxLev) { theMaxSubdivideLevs_ = theMaxLev; }

		void OverrideCurveMeshInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveMeshInfo_ = theInfo; }
		void OverrideMetricInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo) { theMetricInfo_ = theInfo; }

	};
}

#endif // !_Voyage_MetricInfo_Header

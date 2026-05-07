#pragma once
#ifndef _Voyage_PathDiscret_Info_Header
#define _Voyage_PathDiscret_Info_Header

#include <Voyage_Module.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/26/2023 Payvand]
	class Mesh_Curve_Info;
	class NumAlg_AdaptiveInteg_Info;

	class Voyage_PathDiscret_Info
	{

		/*Private Data*/

		std::shared_ptr<Mesh_Curve_Info> theMeshInfo_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theMetricInfo_;

	public:

		static TnbVoyage_EXPORT std::shared_ptr<Mesh_Curve_Info> DEFAULT_CURV_INFO;
		static TnbVoyage_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_INTEG_INFO;

		// default constructor [8/26/2023 Payvand]

		Voyage_PathDiscret_Info()
			: theMeshInfo_(DEFAULT_CURV_INFO)
			, theMetricInfo_(DEFAULT_INTEG_INFO)
		{}

		// constructors [8/26/2023 Payvand]

		// Public functions and operators [8/26/2023 Payvand]

		const auto& MeshInfo() const { return theMeshInfo_; }
		const auto& MetricInfo() const { return theMetricInfo_; }

		void OverrideMeshInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theMeshInfo_ = theInfo; }
		void OverrideMetricInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo) { theMetricInfo_ = theInfo; }

	};
}

#endif // !_Voyage_PathDiscret_Info_Header

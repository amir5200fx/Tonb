#pragma once
#ifndef _Aft2d_gRegionPlaneSurfaceUniMetric_Header
#define _Aft2d_gRegionPlaneSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_gRegionPlaneSurfaceUniMetricFwd.hxx>
#include <Aft2d_gPlnWireSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gRegionPlaneSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gRegionPlaneSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	// Forward Declarations [3/26/2022 Amir]
	class GModel_ParaWire;

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_gPlnWireSurfaceUniMetric>
		Aft2d_gRegionPlaneSurfaceUniMetric::MakeMeshWire<GModel_ParaWire>(const GModel_ParaWire&);
}

#endif // !_Aft2d_gRegionPlaneSurfaceUniMetric_Header

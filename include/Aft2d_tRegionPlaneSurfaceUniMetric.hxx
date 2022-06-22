#pragma once
#ifndef _Aft2d_tRegionPlaneSurfaceUniMetric_Header
#define _Aft2d_tRegionPlaneSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_tRegionPlaneSurfaceUniMetricFwd.hxx>
#include <Aft2d_tPlnWireSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tRegionPlaneSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tRegionPlaneSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	// Forward Declarations [6/22/2022 Amir]
	class TModel_ParaWire;

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_tPlnWireSurfaceUniMetric>
		Aft2d_tRegionPlaneSurfaceUniMetric::MakeMeshWire<TModel_ParaWire>(const TModel_ParaWire&);
}

#endif // !_Aft2d_tRegionPlaneSurfaceUniMetric_Header

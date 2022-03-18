#pragma once
#ifndef _Aft2d_gPatchUniMetric_Header
#define _Aft2d_gPatchUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_PatchTemplate.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_gRegionPlaneSurfaceUniMetricFwd.hxx>
#include <Aft2d_gPatchUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPatchUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPatchUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_gPatchUniMetric_Header

#pragma once
#ifndef _Aft2d_RegionPlaneUniMetric_Header
#define _Aft2d_RegionPlaneUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_RegionPlaneUniMetricFwd.hxx>

namespace tnbLib
{
	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_RegionPlaneUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_RegionPlaneUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_RegionPlaneUniMetric_Header

#pragma once
#ifndef _Aft2d_tPlnWireSurfaceUniMetric_Header
#define _Aft2d_tPlnWireSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_PlnWire.hxx>
#include <Aft2d_tPlnWireSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Entity2d_Box 
		Aft2d_tPlnWireSurfaceUniMetric::CalcBoundingBox(const Aft2d_tPlnCurveSurfaceUniMetric&);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnWireSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnWireSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_tPlnWireSurfaceUniMetric_Header

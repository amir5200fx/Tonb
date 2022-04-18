#pragma once
#ifndef _Mesh2d_PlnWireUniMetric_Header
#define _Mesh2d_PlnWireUniMetric_Header

#include <Mesh_Module.hxx>
#include <Mesh_PlnWire.hxx>
#include <Mesh2d_PlnWireUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Entity2d_Box Mesh2d_PlnWireUniMetric::CalcBoundingBox(const Mesh2d_PlnCurveUniMetric&);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnWireUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnWireUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnWireUniMetric_Header

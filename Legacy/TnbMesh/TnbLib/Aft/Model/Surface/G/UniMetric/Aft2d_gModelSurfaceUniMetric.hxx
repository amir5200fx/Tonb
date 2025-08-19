#pragma once
#ifndef _Aft2d_gModelSurfaceUniMetric_Header
#define _Aft2d_gModelSurfaceUniMetric_Header

#include <Aft_Model.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft2d_FrontSurfaceGlobalData.hxx>
#include <Aft2d_FrontSurfaceInfo.hxx>
#include <Aft2d_gModelSurfaceUniMetricFwd.hxx>
#include <Aft2d_CoreSurfaceUniMetric.hxx>

#include <Aft2d_gModelSurfaceUniMetricI.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gModelSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gModelSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_gModelSurfaceUniMetric_Header

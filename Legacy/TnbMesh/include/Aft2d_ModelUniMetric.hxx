#pragma once
#ifndef _Aft2d_ModelUniMetric_Header
#define _Aft2d_ModelUniMetric_Header

#include <Aft_Model.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_MetricPrcsrUniMetric.hxx>
#include <Aft2d_OptNodeUniMetric_Calculator.hxx>
#include <Aft2d_FrontAnIsoGlobalData.hxx>
#include <Aft2d_FrontAnIsoInfo.hxx>
#include <Aft2d_ModelUniMetricFwd.hxx>
#include <Aft2d_CoreUniMetric.hxx>

#include <Aft2d_ModelUniMetricI.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_ModelUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_ModelUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_ModelUniMetric_Header

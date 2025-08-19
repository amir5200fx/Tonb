#pragma once
#ifndef _Aft2d_CoreBaseSurfaceUniMetricFwd_Header
#define _Aft2d_CoreBaseSurfaceUniMetricFwd_Header

#include <Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd.hxx>
#include <Aft2d_FrontSurfaceInfoFwd.hxx>
#include <Aft2d_FrontSurfaceGlobalDataFwd.hxx>
#include <Aft2d_GlobalDataSurfaceFwd.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2022 Amir]
	template
		<
		class OptNodeAlg,
		class FrontInfo,
		class FrontData,
		class SizeFun,
		class MetricFun
		>
		class Aft_Core_Base;

	typedef Aft_Core_Base
		<
		Aft2d_OptNodeSurfaceUniMetric_Calculator,
		Aft2d_FrontSurfaceInfo,
		Aft2d_FrontSurfaceGlobalData,
		Geo2d_SizeFunction,
		GeoMetricFun2d_Uniform
		>
		Aft2d_CoreBaseSurfaceUniMetric;
}

#endif // !_Aft2d_CoreBaseSurfaceUniMetricFwd_Header

#pragma once
#ifndef _Aft2d_CoreSurfaceUniMetricFwd_Header
#define _Aft2d_CoreSurfaceUniMetricFwd_Header

#include <Aft2d_FrontSurfaceInfoFwd.hxx>
#include <Aft2d_FrontSurfaceGlobalDataFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template
		<
		class OptNodeAlg,
		class SizeFun,
		class FrontInfo,
		class FrontData,
		class MetricFun
		>
		class Aft_Core;

	typedef Aft_Core
		<
		Aft2d_OptNodeSurfaceUniMetric_Calculator,
		Geo2d_SizeFunction,
		Aft2d_FrontSurfaceInfo, Aft2d_FrontSurfaceGlobalData,
		GeoMetricFun2d_Uniform> Aft2d_CoreSurfaceUniMetric;
}

#endif // !_Aft2d_CoreSurfaceUniMetricFwd_Header

#pragma once
#ifndef _Aft2d_CoreUniMetricFwd_Header
#define _Aft2d_CoreUniMetricFwd_Header

#include <Aft2d_FrontAnIsoInfoFwd.hxx>
#include <Aft2d_FrontAnIsoGlobalDataFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_OptNodeUniMetric_CalculatorFwd.hxx>

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
		Aft2d_OptNodeUniMetric_Calculator,
		Geo2d_SizeFunction,
		Aft2d_FrontAnIsoInfo,
		Aft2d_FrontAnIsoGlobalData,
		GeoMetricFun2d_Uniform
		> Aft2d_CoreUniMetric;
}

#endif // !_Aft2d_CoreUniMetricFwd_Header

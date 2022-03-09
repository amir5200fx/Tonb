#pragma once
#ifndef _Aft2d_CorrOptNodeSurfaceUniMetric_IterativeFwd_Header
#define _Aft2d_CorrOptNodeSurfaceUniMetric_IterativeFwd_Header

#include <Aft_OptNode_CorrectorType.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/6/2022 Amir]
	template
		<
		Aft_OptNode_CorrectorType Type,
		class FrontType,
		class InfoType,
		class SizeFun,
		class OptNodeCalculator,
		class MetricFun
		>
		class Aft_OptNode_Corrector;

	class Aft_SizeCorr_IterativeInfo;

	typedef Aft_OptNode_Corrector
		<
		aft_optNode_corrector_iterative,
		Aft2d_EdgeSurface,
		Aft_SizeCorr_IterativeInfo,
		Geo2d_SizeFunction,
		void,
		GeoMetricFun2d_Uniform
		>
		Aft2d_CorrOptNodeSurfaceUniMetric_Iterative;
}

#endif // !_Aft2d_CorrOptNodeSurfaceUniMetric_IterativeFwd_Header

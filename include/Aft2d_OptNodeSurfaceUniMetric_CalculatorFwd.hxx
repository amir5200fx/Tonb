#pragma once
#ifndef _Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd_Header
#define _Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/6/2022 Amir]
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode_Calculator;

	typedef Aft_OptNode_Calculator<Aft2d_EdgeSurface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_OptNodeSurfaceUniMetric_Calculator;
}

#endif // !_Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd_Header

#pragma once
#ifndef _Aft2d_OptNodeUniMetric_CalculatorFwd_Header
#define _Aft2d_OptNodeUniMetric_CalculatorFwd_Header

#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/3/2022 Amir]
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode_Calculator;

	typedef Aft_OptNode_Calculator<Aft2d_EdgeAnIso, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_OptNodeUniMetric_Calculator;
}

#endif // !_Aft2d_OptNodeUniMetric_CalculatorFwd_Header

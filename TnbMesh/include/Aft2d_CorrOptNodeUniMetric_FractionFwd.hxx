#pragma once
#ifndef _Aft2d_CorrOptNodeUniMetric_FractionFwd_Header
#define _Aft2d_CorrOptNodeUniMetric_FractionFwd_Header

#include <Aft_OptNode_CorrectorType.hxx>
#include <Aft2d_OptNodeUniMetric_CalculatorFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

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

	class Aft_SizeCorr_FractionInfo;

	typedef Aft_OptNode_Corrector
		<
		aft_optNode_corrector_fraction,
		Aft2d_EdgeAnIso,
		Aft_SizeCorr_FractionInfo,
		Geo2d_SizeFunction,
		Aft2d_OptNodeUniMetric_Calculator,
		GeoMetricFun2d_Uniform
		> Aft2d_CorrOptNodeUniMetric_Fraction;
}


#endif // !_Aft2d_CorrOptNodeUniMetric_FractionFwd_Header

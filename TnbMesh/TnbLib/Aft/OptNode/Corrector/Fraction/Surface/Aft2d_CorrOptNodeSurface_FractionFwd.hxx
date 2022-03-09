#pragma once
#ifndef _Aft2d_CorrOptNodeSurface_FractionFwd_Header
#define _Aft2d_CorrOptNodeSurface_FractionFwd_Header

#include <Aft_OptNode_CorrectorType.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Aft2d_OptNodeSurface_CalculatorFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/5/2022 Amir]
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
		Aft2d_EdgeSurface,
		Aft_SizeCorr_FractionInfo,
		Geo2d_SizeFunction,
		Aft2d_OptNodeSurface_Calculator,
		Geo2d_MetricFunction
		> Aft2d_CorrOptNodeSurface_Fraction;
}

#endif // !_Aft2d_CorrOptNodeSurface_FractionFwd_Header

#pragma once
#ifndef _Aft2d_OptNodeAnIso_nonIterAdaptiveFwd_Header
#define _Aft2d_OptNodeAnIso_nonIterAdaptiveFwd_Header

#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Aft2d_CorrOptNodeAnIso_FractionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/5/2022 Amir]
	template
		<
		class FrontType,
		class SizeFun,
		class MetricFun,
		class CorrAlg,
		class AltrAlg
		>
		class Aft_OptNode;

	typedef Aft_OptNode
		<
		Aft2d_EdgeAnIso, 
		Geo2d_SizeFunction,
		Geo2d_MetricFunction, 
		Aft2d_CorrOptNodeAnIso_Fraction, 
		void
		>
		Aft2d_OptNodeAnIso_nonIterAdaptive;
}

#endif // !_Aft2d_OptNodeAnIso_nonIterAdaptiveFwd_Header

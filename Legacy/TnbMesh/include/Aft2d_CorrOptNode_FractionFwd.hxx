#pragma once
#ifndef _Aft2d_CorrOptNode_FractionFwd_Header
#define _Aft2d_CorrOptNode_FractionFwd_Header

#include <Aft_OptNode_CorrectorType.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Aft2d_EdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/1/2022 Amir]
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
		Aft2d_Edge,
		Aft_SizeCorr_FractionInfo,
		Geo2d_SizeFunction,
		void,
		void
		> Aft2d_CorrOptNode_Fraction;
}

#endif // !_Aft2d_CorrOptNode_FractionFwd_Header

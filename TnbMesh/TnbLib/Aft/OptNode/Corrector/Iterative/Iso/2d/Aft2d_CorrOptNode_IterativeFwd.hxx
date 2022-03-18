#pragma once
#ifndef _Aft2d_CorrOptNode_IterativeFwd_Header
#define _Aft2d_CorrOptNode_IterativeFwd_Header

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

	class Aft_SizeCorr_IterativeInfo;

	typedef Aft_OptNode_Corrector
		<
		aft_optNode_corrector_iterative,
		Aft2d_Edge, 
		Aft_SizeCorr_IterativeInfo, 
		Geo2d_SizeFunction,
		void,
		void
		>
		Aft2d_CorrOptNode_Iterative;
}

#endif // !_Aft2d_CorrOptNode_IterativeFwd_Header

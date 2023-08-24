#pragma once
#ifndef _VoyageMesh_CorrOptNode_IterativeFwd_Header
#define _VoyageMesh_CorrOptNode_IterativeFwd_Header

#include <Aft_OptNode_CorrectorType.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
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

	class VoyageMesh_Edge;
	class Aft_SizeCorr_IterativeInfo;

	typedef Aft_OptNode_Corrector
		<
		aft_optNode_corrector_iterative,
		VoyageMesh_Edge,
		Aft_SizeCorr_IterativeInfo,
		Geo2d_SizeFunction,
		void,
		Geo2d_MetricFunction
		>
		VoyageMesh_CorrOptNode_Iterative;
}

#endif // !_VoyageMesh_CorrOptNode_IterativeFwd_Header

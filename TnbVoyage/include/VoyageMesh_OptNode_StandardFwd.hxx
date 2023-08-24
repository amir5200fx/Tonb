#pragma once
#ifndef _VoyageMesh_OptNode_StandardFwd_Header
#define _VoyageMesh_OptNode_StandardFwd_Header

#include <VoyageMesh_CorrOptNode_IterativeFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{
	// Forward Declarations [8/23/2023 aamir]
	template
		<
		class FrontType,
		class SizeFun,
		class MetricFun,
		class CorrAlg,
		class AltrAlg
		>
		class Aft_OptNode;

	class VoyageMesh_Edge;

	typedef Aft_OptNode
		<
		VoyageMesh_Edge,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction,
		VoyageMesh_CorrOptNode_Iterative,
		void
		>
		VoyageMesh_OptNode_Standard;
}

#endif // !_VoyageMesh_OptNode_StandardFwd_Header

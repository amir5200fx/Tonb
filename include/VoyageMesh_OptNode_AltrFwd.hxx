#pragma once
#ifndef _VoyageMesh_OptNode_AltrFwd_Header
#define _VoyageMesh_OptNode_AltrFwd_Header

#include <VoyageMesh_CorrOptNode_IterativeFwd.hxx>
#include <VoyageMesh_AltrOptNodeFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/7/2022 Amir]
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
		VoyageMesh_Edge,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction,
		VoyageMesh_CorrOptNode_Iterative,
		VoyageMesh_AltrOptNode
		>
		VoyageMesh_OptNode_Altr;
}

#endif // !_VoyageMesh_OptNode_AltrFwd_Header

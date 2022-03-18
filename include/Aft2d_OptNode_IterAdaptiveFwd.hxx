#pragma once
#ifndef _Aft2d_OptNode_IterAdaptiveFwd_Header
#define _Aft2d_OptNode_IterAdaptiveFwd_Header

#include <Aft2d_EdgeFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Aft2d_CorrOptNode_IterativeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/1/2022 Amir]
	template
		<
		class FrontType,
		class SizeFun,
		class MetricFun,
		class CorrAlg,
		class AltrAlg
		>
		class Aft_OptNode;

	typedef Aft_OptNode<Aft2d_Edge, Geo2d_SizeFunction, void, Aft2d_CorrOptNode_Iterative, void>
		Aft2d_OptNode_IterAdaptive;
}

#endif // !_Aft2d_OptNode_IterAdaptiveFwd_Header

#pragma once
#ifndef _MeshPostAF2d_OptNode_CalculatorFwd_Header
#define _MeshPostAF2d_OptNode_CalculatorFwd_Header

#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	class MeshPostAF2d_Edge;

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode_Calculator;

	typedef Aft_OptNode_Calculator<MeshPostAF2d_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		MeshPostAF2d_OptNode_Calculator;

}

#endif // !_MeshPostAF2d_OptNode_CalculatorFwd_Header

#pragma once
#ifndef _VoyageMesh_OptNode_CalculatorFwd_Header
#define _VoyageMesh_OptNode_CalculatorFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	class VoyageMesh_Edge;
	
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_OptNode_Calculator;

	typedef Aft_OptNode_Calculator<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		VoyageMesh_OptNode_Calculator;
}

#endif // !_VoyageMesh_OptNode_CalculatorFwd_Header

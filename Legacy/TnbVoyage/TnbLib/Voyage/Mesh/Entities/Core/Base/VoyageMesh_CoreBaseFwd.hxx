#pragma once
#ifndef _VoyageMesh_CoreBaseFwd_Header
#define _VoyageMesh_CoreBaseFwd_Header

#include <VoyageMesh_OptNode_CalculatorFwd.hxx>
#include <VoyageMesh_FrontInfoFwd.hxx>
#include <VoyageMesh_FrontGlobalDataFwd.hxx>
#include <VoyageMesh_GlobalDataFwd.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2022 Amir]
	template
		<
		class OptNodeAlg,
		class FrontInfo,
		class FrontData,
		class SizeFun,
		class MetricFun
		>
		class Aft_Core_Base;

	typedef Aft_Core_Base
		<
		VoyageMesh_OptNode_Calculator,
		VoyageMesh_FrontInfo,
		VoyageMesh_FrontGlobalData,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		>
		VoyageMesh_CoreBase;

}

#endif // !_VoyageMesh_CoreBaseFwd_Header

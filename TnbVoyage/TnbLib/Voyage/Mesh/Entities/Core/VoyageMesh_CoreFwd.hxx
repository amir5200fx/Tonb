#pragma once
#ifndef _VoyageMesh_CoreFwd_Header
#define _VoyageMesh_CoreFwd_Header

#include <VoyageMesh_OptNode_CalculatorFwd.hxx>
#include <VoyageMesh_FrontGlobalDataFwd.hxx>
#include <VoyageMesh_FrontInfoFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	//  Forward Declarations [8/12/2023 aamir]
	template
		<
		class OptNodeAlg,
		class SizeFun,
		class FrontInfo,
		class FrontData,
		class MetricFun
		>
		class Aft_Core;

	typedef Aft_Core
		<
		VoyageMesh_OptNode_Calculator,
		Geo2d_SizeFunction,
		VoyageMesh_FrontInfo, VoyageMesh_FrontGlobalData,
		Geo2d_MetricFunction> VoyageMesh_Core;

}

#endif // !_VoyageMesh_CoreFwd_Header

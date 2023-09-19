#pragma once
#ifndef _MeshPostAF2d_CoreBaseFwd_Header
#define _MeshPostAF2d_CoreBaseFwd_Header

#include <MeshPostAF2d_OptNode_CalculatorFwd.hxx>
#include <MeshPostAF2d_FrontInfoFwd.hxx>
#include <MeshPostAF2d_FrontGlobalDataFwd.hxx>
#include <MeshPostAF2d_GlobalDataFwd.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
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
		MeshPostAF2d_OptNode_Calculator,
		MeshPostAF2d_FrontInfo,
		MeshPostAF2d_FrontGlobalData,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		>
		MeshPostAF2d_CoreBase;

}

#endif // !_MeshPostAF2d_CoreBaseFwd_Header

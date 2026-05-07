#pragma once
#ifndef _MeshPostAF2d_CoreFwd_Header
#define _MeshPostAF2d_CoreFwd_Header

#include <MeshPostAF2d_OptNode_CalculatorFwd.hxx>
#include <MeshPostAF2d_FrontGlobalDataFwd.hxx>
#include <MeshPostAF2d_FrontInfoFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
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
		MeshPostAF2d_OptNode_Calculator,
		Geo2d_SizeFunction,
		MeshPostAF2d_FrontInfo, MeshPostAF2d_FrontGlobalData,
		Geo2d_MetricFunction> MeshPostAF2d_Core;
}

#endif // !_MeshPostAF2d_CoreFwd_Header

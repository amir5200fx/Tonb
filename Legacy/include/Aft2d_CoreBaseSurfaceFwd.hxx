#pragma once
#ifndef _Aft2d_CoreBaseSurfaceFwd_Header
#define _Aft2d_CoreBaseSurfaceFwd_Header

#include <Aft2d_OptNodeSurface_CalculatorFwd.hxx>
#include <Aft2d_FrontSurfaceInfoFwd.hxx>
#include <Aft2d_FrontSurfaceGlobalDataFwd.hxx>
#include <Aft2d_GlobalDataSurfaceFwd.hxx>
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
		Aft2d_OptNodeSurface_Calculator,
		Aft2d_FrontSurfaceInfo,
		Aft2d_FrontSurfaceGlobalData,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		>
		Aft2d_CoreBaseSurface;

}


#endif // !_Aft2d_CoreBaseSurfaceFwd_Header

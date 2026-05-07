#pragma once
#ifndef _Aft2d_CoreBaseAnIsoFwd_Header
#define _Aft2d_CoreBaseAnIsoFwd_Header

#include <Aft2d_OptNodeAnIso_CalculatorFwd.hxx>
#include <Aft2d_FrontAnIsoInfoFwd.hxx>
#include <Aft2d_FrontAnIsoGlobalDataFwd.hxx>
#include <Aft2d_GlobalDataAnIsoFwd.hxx>
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
		Aft2d_OptNodeAnIso_Calculator,
		Aft2d_FrontAnIsoInfo,
		Aft2d_FrontAnIsoGlobalData,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		>
		Aft2d_CoreBaseAnIso;
}

#endif // !_Aft2d_CoreBaseAnIsoFwd_Header

#pragma once
#ifndef _Aft2d_CoreBaseFwd_Header
#define _Aft2d_CoreBaseFwd_Header

#include <Aft2d_OptNode_CalculatorFwd.hxx>
#include <Aft2d_FrontInfoFwd.hxx>
#include <Aft2d_FrontGlobalDataFwd.hxx>
#include <Aft2d_GlobalDataFwd.hxx>
#include <Geo2d_SizeFunction.hxx>

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
		Aft2d_OptNode_Calculator,
		Aft2d_FrontInfo,
		Aft2d_FrontGlobalData,
		Geo2d_SizeFunction,
		void
		>
		Aft2d_CoreBase;
}

#endif // !_Aft2d_CoreBaseFwd_Header

#pragma once
#ifndef _Aft3d_CoreBaseFwd_Header
#define _Aft3d_CoreBaseFwd_Header

#include <Aft3d_OptNode_CalculatorFwd.hxx>
#include <Aft3d_FrontInfoFwd.hxx>
#include <Aft3d_FrontGlobalDataFwd.hxx>
#include <Aft3d_GlobalDataFwd.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/17/2022 Payvand]
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
		Aft3d_OptNode_Calculator,
		Aft3d_FrontInfo,
		Aft3d_FrontGlobalData,
		Geo3d_SizeFunction,
		void
		> 
		Aft3d_CoreBase;
}

#endif // !_Aft3d_CoreBaseFwd_Header

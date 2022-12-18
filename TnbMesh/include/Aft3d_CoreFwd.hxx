#pragma once
#ifndef _Aft3d_CoreFwd_Header
#define _Aft3d_CoreFwd_Header

#include <Aft3d_FacetFwd.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Geo3d_MetricFunctionFwd.hxx>
#include <Aft3d_FrontInfoFwd.hxx>
#include <Aft3d_FrontGlobalDataFwd.hxx>
#include <Aft3d_OptNode_CalculatorFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template
		<
		class OptNodeAlg, class SizeFun,
		class FrontInfo, class FrontData,
		class MetricFun
		>
		class Aft_Core;

	typedef Aft_Core
		<
		Aft3d_OptNode_Calculator,
		Geo3d_SizeFunction, 
		Aft3d_FrontInfo,
		Aft3d_FrontGlobalData,
		void
		>
		Aft3d_Core;
}

#endif // !_Aft3d_CoreFwd_Header

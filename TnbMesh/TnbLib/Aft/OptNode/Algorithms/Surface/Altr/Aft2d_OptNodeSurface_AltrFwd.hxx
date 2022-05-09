#pragma once
#ifndef _Aft2d_OptNodeSurface_AltrFwd_Header
#define _Aft2d_OptNodeSurface_AltrFwd_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Aft2d_CorrOptNodeSurface_IterativeFwd.hxx>
#include <Aft2d_AltrOptNodeSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/7/2022 Amir]
	template
		<
		class FrontType,
		class SizeFun,
		class MetricFun,
		class CorrAlg,
		class AltrAlg
		>
		class Aft_OptNode;

	typedef Aft_OptNode
		<
		Aft2d_EdgeSurface,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction,
		Aft2d_CorrOptNodeSurface_Iterative,
		Aft2d_AltrOptNodeSurface
		>
		Aft2d_OptNodeSurface_Altr;
}

#endif // !_Aft2d_OptNodeSurface_AltrFwd_Header

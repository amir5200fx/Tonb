#pragma once
#ifndef _Aft2d_AltrOptNodeSurfaceFwd_Header
#define _Aft2d_AltrOptNodeSurfaceFwd_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/7/2022 Amir]
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_AltrOptNode;

	typedef Aft_AltrOptNode<Aft2d_EdgeSurface, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_AltrOptNodeSurface;
}

#endif // !_Aft2d_AltrOptNodeSurfaceFwd_Header

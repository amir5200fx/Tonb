#pragma once
#ifndef _Aft2d_gBoundaryOfPlaneSurfaceFwd_Header
#define _Aft2d_gBoundaryOfPlaneSurfaceFwd_Header

#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_gRegionPlaneSurface, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_gBoundaryOfPlaneSurface;
}

#endif // !_Aft2d_gBoundaryOfPlaneSurfaceFwd_Header

#pragma once
#ifndef _Aft2d_tBoundaryOfPlaneSurfaceFwd_Header
#define _Aft2d_tBoundaryOfPlaneSurfaceFwd_Header

#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_tRegionPlaneSurface, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_tBoundaryOfPlaneSurface;
}

#endif // !_Aft2d_tBoundaryOfPlaneSurfaceFwd_Header

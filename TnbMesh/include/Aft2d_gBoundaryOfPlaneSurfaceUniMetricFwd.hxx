#pragma once
#ifndef _Aft2d_gBoundaryOfPlaneSurfaceUniMetricFwd_Header
#define _Aft2d_gBoundaryOfPlaneSurfaceUniMetricFwd_Header

#include <Aft2d_gRegionPlaneSurfaceUniMetricFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_gRegionPlaneSurfaceUniMetric, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_gBoundaryOfPlaneSurfaceUniMetric;
}

#endif // !_Aft2d_gBoundaryOfPlaneSurfaceUniMetricFwd_Header

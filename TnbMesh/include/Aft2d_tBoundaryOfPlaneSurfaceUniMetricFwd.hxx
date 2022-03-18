#pragma once
#ifndef _Aft2d_tBoundaryOfPlaneSurfaceUniMetricFwd_Header
#define _Aft2d_tBoundaryOfPlaneSurfaceUniMetricFwd_Header

#include <Aft2d_tRegionPlaneSurfaceUniMetricFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_tRegionPlaneSurfaceUniMetric, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_tBoundaryOfPlaneSurfaceUniMetric;
}

#endif // !_Aft2d_tBoundaryOfPlaneSurfaceUniMetricFwd_Header

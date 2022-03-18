#pragma once
#ifndef _Aft2d_MetricPrcsrSurfaceUniMetricFwd_Header
#define _Aft2d_MetricPrcsrSurfaceUniMetricFwd_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/6/2022 Amir]
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	typedef Aft_MetricPrcsr<Aft2d_EdgeSurface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_MetricPrcsrSurfaceUniMetric;
}

#endif // !_Aft2d_MetricPrcsrSurfaceUniMetricFwd_Header

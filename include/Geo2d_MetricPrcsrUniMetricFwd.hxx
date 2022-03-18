#pragma once
#ifndef _Geo2d_MetricPrcsrUniMetricFwd_Header
#define _Geo2d_MetricPrcsrUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	typedef Geo_MetricPrcsr<Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Geo2d_MetricPrcsrUniMetric;
}

#endif // !_Geo2d_MetricPrcsrUniMetricFwd_Header

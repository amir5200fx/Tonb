#pragma once
#ifndef _Aft2d_MetricPrcsrUniMetricFwd_Header
#define _Aft2d_MetricPrcsrUniMetricFwd_Header

#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	typedef Aft_MetricPrcsr<Aft2d_EdgeAnIso, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_MetricPrcsrUniMetric;
}

#endif // !_Aft2d_MetricPrcsrUniMetricFwd_Header

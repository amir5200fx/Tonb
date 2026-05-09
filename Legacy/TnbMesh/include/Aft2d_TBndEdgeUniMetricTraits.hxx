#pragma once
#ifndef _Aft2d_TBndEdgeUniMetricTraits_Header
#define _Aft2d_TBndEdgeUniMetricTraits_Header

#include <Aft2d_BndEdgeAnIsoTraits.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_PlnCurveUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	struct Aft2d_TBndEdgeUniMetricTraits
	{

		typedef Aft2d_BndEdgeAnIsoTraits bndEdgeTraits;

		typedef Aft2d_PlnCurveUniMetric curveType;
		typedef void surfType;
		typedef Geo2d_MetricPrcsrUniMetric metricPrcsr;
	};
}

#endif // !_Aft2d_TBndEdgeUniMetricTraits_Header

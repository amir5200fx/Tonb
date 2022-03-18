#pragma once
#ifndef _Aft2d_tBndEdgeSurfaceUniMetricTraits_Header
#define _Aft2d_tBndEdgeSurfaceUniMetricTraits_Header

#include <Aft2d_BndEdgeSurfaceTraits.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/20/2021 Amir]

	class TModel_ParaCurve;

	struct Aft2d_tBndEdgeSurfaceUniMetricTraits
	{
		typedef Aft2d_BndEdgeSurfaceTraits bndEdgeTraits;

		typedef typename Aft2d_tPlnCurveSurfaceUniMetric curveType;
		typedef void surfType;
		typedef typename Geo2d_MetricPrcsrUniMetric metricPrcsr;
	};
}

#endif // !_Aft2d_tBndEdgeSurfaceUniMetricTraits_Header

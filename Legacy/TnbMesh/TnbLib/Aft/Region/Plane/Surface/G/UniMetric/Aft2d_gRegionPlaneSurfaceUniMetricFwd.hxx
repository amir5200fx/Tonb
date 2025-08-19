#pragma once
#ifndef _Aft2d_gRegionPlaneSurfaceUniMetricFwd_Header
#define _Aft2d_gRegionPlaneSurfaceUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class GModel_ParaCurve;

	typedef Mesh_RegionPlane<GModel_ParaCurve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_gRegionPlaneSurfaceUniMetric;
}

#endif // !_Aft2d_gRegionPlaneSurfaceUniMetricFwd_Header

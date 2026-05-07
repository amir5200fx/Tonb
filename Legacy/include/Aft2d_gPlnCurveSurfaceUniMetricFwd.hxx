#pragma once
#ifndef _Aft2d_gPlnCurveSurfaceUniMetricFwd_Header
#define _Aft2d_gPlnCurveSurfaceUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_PlnCurve;

	class GModel_ParaCurve;

	typedef Mesh_PlnCurve<GModel_ParaCurve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_gPlnCurveSurfaceUniMetric;
}

#endif // !_Aft2d_gPlnCurveSurfaceUniMetricFwd_Header

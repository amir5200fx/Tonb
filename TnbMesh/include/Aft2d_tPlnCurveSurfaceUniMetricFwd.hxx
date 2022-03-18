#pragma once
#ifndef _Aft2d_tPlnCurveSurfaceUniMetricFwd_Header
#define _Aft2d_tPlnCurveSurfaceUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_PlnCurve;

	class TModel_ParaCurve;

	typedef Mesh_PlnCurve<TModel_ParaCurve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_tPlnCurveSurfaceUniMetric;
}

#endif // !_Aft2d_tPlnCurveSurfaceUniMetricFwd_Header

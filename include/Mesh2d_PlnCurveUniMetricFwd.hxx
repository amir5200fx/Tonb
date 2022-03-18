#pragma once
#ifndef _Mesh2d_PlnCurveUniMetricFwd_Header
#define _Mesh2d_PlnCurveUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_PlnCurve;

	class Pln_Curve;

	typedef Mesh_PlnCurve<Pln_Curve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Mesh2d_PlnCurveUniMetric;
}

#endif // !_Mesh2d_PlnCurveUniMetricFwd_Header

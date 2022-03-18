#pragma once
#ifndef _Aft2d_RegionPlaneUniMetricFwd_Header
#define _Aft2d_RegionPlaneUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft2d_PlnCurveUniMetricFwd.hxx>
#include <Aft2d_PlnWireUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class Pln_Curve;

	typedef Mesh_RegionPlane<Pln_Curve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_RegionPlaneUniMetric;
}

#endif // !_Aft2d_RegionPlaneUniMetricFwd_Header

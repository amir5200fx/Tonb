#pragma once
#ifndef _Aft2d_tPatchUniMetricFwd_Header
#define _Aft2d_tPatchUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/19/2021 Amir]

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_PatchTemplate;

	class TModel_Surface;

	typedef Mesh_PatchTemplate<TModel_Surface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_tPatchUniMetric;
}

#endif // !_Aft2d_tPatchUniMetricFwd_Header

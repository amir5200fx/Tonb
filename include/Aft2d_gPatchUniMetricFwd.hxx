#pragma once
#ifndef _Aft2d_gPatchUniMetricFwd_Header
#define _Aft2d_gPatchUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/19/2021 Amir]

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_PatchTemplate;

	class GModel_Surface;

	typedef Mesh_PatchTemplate<GModel_Surface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_gPatchUniMetric;
}

#endif // !_Aft2d_gPatchUniMetricFwd_Header

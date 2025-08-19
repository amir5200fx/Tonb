#pragma once
#ifndef _Aft2d_gModelSurfaceUniMetricFwd_Header
#define _Aft2d_gModelSurfaceUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2022 Amir]
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class GModel_Plane;

	typedef Aft_Model<GModel_Plane, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_gModelSurfaceUniMetric;
}

#endif // !_Aft2d_gModelSurfaceUniMetricFwd_Header

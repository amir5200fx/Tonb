#pragma once
#ifndef _Aft2d_tModelSurfaceUniMetricFwd_Header
#define _Aft2d_tModelSurfaceUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2022 Amir]
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class TModel_Plane;

	typedef Aft_Model<TModel_Plane, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_tModelSurfaceUniMetric;
}

#endif // !_Aft2d_tModelSurfaceUniMetricFwd_Header

#pragma once
#ifndef _Aft2d_ModelUniMetricFwd_Header
#define _Aft2d_ModelUniMetricFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_Uniform.hxx>

namespace tnbLib
{

	// Forward Declarations [3/8/2022 Amir]
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class Cad2d_Plane;

	typedef Aft_Model<Cad2d_Plane, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		Aft2d_ModelUniMetric;
}

#endif // !_Aft2d_ModelUniMetricFwd_Header

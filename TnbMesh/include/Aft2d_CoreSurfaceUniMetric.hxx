#pragma once
#ifndef _Aft2d_CoreSurfaceUniMetric_Header
#define _Aft2d_CoreSurfaceUniMetric_Header

#include <Aft2d_CoreSurfaceTemplate.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft2d_CoreSurfaceUniMetricFwd.hxx>
#include <Aft2d_CoreBaseSurfaceUniMetric.hxx>

namespace tnbLib
{

	typedef Aft2d_CoreSurfaceTemplate
		<
		Aft2d_OptNodeSurfaceUniMetric_Calculator,
		Geo2d_SizeFunction,
		GeoMetricFun2d_Uniform
		> Aft2d_CoreSurfaceUniMetric;
}

#endif // !_Aft2d_CoreSurfaceUniMetric_Header

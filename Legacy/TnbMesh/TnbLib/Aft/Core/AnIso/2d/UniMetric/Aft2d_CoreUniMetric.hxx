#pragma once
#ifndef _Aft2d_CoreUniMetric_Header
#define _Aft2d_CoreUniMetric_Header

#include <Aft2d_CoreAnIsoTemplate.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_OptNodeUniMetric_Calculator.hxx>
#include <Aft2d_CoreUniMetricFwd.hxx>
#include <Aft2d_CoreBaseUniMetric.hxx>

namespace tnbLib
{

	typedef Aft2d_CoreAnIsoTemplate
		<
		Aft2d_OptNodeUniMetric_Calculator,
		Geo2d_SizeFunction, GeoMetricFun2d_Uniform
		>
		Aft2d_CoreUniMetric;
}

#endif // !_Aft2d_CoreUniMetric_Header

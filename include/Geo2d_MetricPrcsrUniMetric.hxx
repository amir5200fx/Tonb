#pragma once
#ifndef _Geo2d_MetricPrcsrUniMetric_Header
#define _Geo2d_MetricPrcsrUniMetric_Header

#include <Geo_MetricPrcsr.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Entity2d_Metric1.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT Standard_Real
		Geo2d_MetricPrcsrUniMetric::CalcDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;

	template<>
	TnbMesh_EXPORT Standard_Real
		Geo2d_MetricPrcsrUniMetric::CalcUnitDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo2d_MetricPrcsrUniMetric);

#endif // !_Geo2d_MetricPrcsrUniMetric_Header

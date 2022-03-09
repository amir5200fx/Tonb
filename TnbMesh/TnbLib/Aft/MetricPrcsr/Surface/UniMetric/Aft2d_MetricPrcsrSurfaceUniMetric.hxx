#pragma once
#ifndef _Aft2d_MetricPrcsrSurfaceUniMetric_Header
#define _Aft2d_MetricPrcsrSurfaceUniMetric_Header

#include <Aft_MetricPrcsr.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurfaceUniMetric::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Entity2d_Metric1& theMetric,
		const Pnt2d& theCentre
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurfaceUniMetric::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& theFront
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurfaceUniMetric::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Aft2d_EdgeSurface& theFront
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurfaceUniMetric::CalcEffectiveFront
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& theFront
	) const;
}

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric);

#endif // !_Aft2d_MetricPrcsrSurfaceUniMetric_Header

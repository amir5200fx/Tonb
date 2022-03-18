#pragma once
#ifndef _Aft2d_tPlnCurveSurfaceUniMetric_Header
#define _Aft2d_tPlnCurveSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <TModel_ParaCurve.hxx>
#include <Mesh_PlnCurve.hxx>
//#include <Geo2d_SizeFunction.hxx>
//#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetricFwd.hxx>
#include <Aft2d_tSegmentEdgeUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnCurveSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnCurveSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>
		Aft2d_tPlnCurveSurfaceUniMetric::TopoMesh<Aft2d_tSegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_tPlnCurveSurfaceUniMetric_Header

#pragma once
#ifndef _Aft2d_gPlnCurveSurfaceUniMetric_Header
#define _Aft2d_gPlnCurveSurfaceUniMetric_Header

#include <Mesh_Module.hxx>
#include <GModel_ParaCurve.hxx>
#include <Mesh_PlnCurve.hxx>
//#include <Geo2d_SizeFunction.hxx>
//#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetricFwd.hxx>
#include <Aft2d_gSegmentEdgeUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnCurveSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnCurveSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>
		Aft2d_gPlnCurveSurfaceUniMetric::TopoMesh<Aft2d_gSegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_gPlnCurveSurfaceUniMetric_Header

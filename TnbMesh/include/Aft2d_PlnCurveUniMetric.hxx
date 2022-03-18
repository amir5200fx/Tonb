#pragma once
#ifndef _Aft2d_PlnCurveUniMetric_Header
#define _Aft2d_PlnCurveUniMetric_Header

#include <Mesh2d_PlnCurveUniMetric.hxx>
#include <Aft2d_PlnCurveUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>
#include <Aft2d_SegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{


	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>
		Aft2d_PlnCurveUniMetric::TopoMesh<Aft2d_SegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_PlnCurveUniMetric_Header

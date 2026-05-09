#pragma once
#ifndef _Aft2d_SegmentGapEdgeUniMetric_Header
#define _Aft2d_SegmentGapEdgeUniMetric_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_SegmentGapEdgeUniMetricFwd.hxx>
#include <Aft2d_SegmentEdgeUniMetric.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_SegmentGapEdgeUniMetric::Contraction
	(
		const Geo2d_MetricPrcsrUniMetric&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>
		Aft2d_SegmentGapEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_PlnCurveUniMetric>&
		);
}

#endif // !_Aft2d_SegmentGapEdgeUniMetric_Header

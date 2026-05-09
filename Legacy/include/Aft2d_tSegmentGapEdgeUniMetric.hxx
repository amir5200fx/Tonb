#pragma once
#ifndef _Aft2d_tSegmentGapEdgeUniMetric_Header
#define _Aft2d_tSegmentGapEdgeUniMetric_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_tSegmentGapEdgeUniMetricFwd.hxx>
#include <Aft2d_tSegmentEdgeUniMetric.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_tSegmentGapEdgeUniMetric::Contraction
	(
		const Geo2d_MetricPrcsrUniMetric&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>
		Aft2d_tSegmentGapEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>&
		);
}

#endif // !_Aft2d_tSegmentGapEdgeUniMetric_Header

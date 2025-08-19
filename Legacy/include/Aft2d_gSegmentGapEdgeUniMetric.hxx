#pragma once
#ifndef _Aft2d_gSegmentGapEdgeUniMetric_Header
#define _Aft2d_gSegmentGapEdgeUniMetric_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_gSegmentGapEdgeUniMetricFwd.hxx>
#include <Aft2d_gSegmentEdgeUniMetric.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_gSegmentGapEdgeUniMetric::Contraction
	(
		const Geo2d_MetricPrcsrUniMetric&
	);
	
	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>
		Aft2d_gSegmentGapEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>&
		);
}

#endif // !_Aft2d_gSegmentGapEdgeUniMetric_Header

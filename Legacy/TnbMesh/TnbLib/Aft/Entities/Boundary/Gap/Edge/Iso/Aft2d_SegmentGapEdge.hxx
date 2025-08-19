#pragma once
#ifndef _Aft2d_SegmentGapEdge_Header
#define _Aft2d_SegmentGapEdge_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_SegmentGapEdgeFwd.hxx>
#include <Aft2d_SegmentEdge.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_SegmentGapEdge::Contraction
	(
		const Geo2d_MetricPrcsr&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdge>>
		Aft2d_SegmentGapEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_PlnCurve>&
		);
}

#endif // !_Aft2d_SegmentGapEdge_Header

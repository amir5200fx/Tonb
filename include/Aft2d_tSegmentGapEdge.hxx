#pragma once
#ifndef _Aft2d_tSegmentGapEdge_Header
#define _Aft2d_tSegmentGapEdge_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_tSegmentGapEdgeFwd.hxx>
#include <Aft2d_tSegmentEdge.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_tSegmentGapEdge::Contraction
	(
		const Geo2d_MetricPrcsrAnIso&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Aft2d_tSegmentGapEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_tPlnCurveSurface>&
		);
}

#endif // !_Aft2d_tSegmentGapEdge_Header

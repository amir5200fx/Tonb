#pragma once
#ifndef _Aft2d_gSegmentGapEdge_Header
#define _Aft2d_gSegmentGapEdge_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_gSegmentGapEdgeFwd.hxx>
#include <Aft2d_gSegmentEdge.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_gSegmentGapEdge::Contraction
	(
		const Geo2d_MetricPrcsrAnIso&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gSegmentGapEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_gPlnCurveSurface>&
		);
}

#endif // !_Aft2d_gSegmentGapEdge_Header

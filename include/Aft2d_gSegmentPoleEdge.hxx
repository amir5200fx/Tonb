#pragma once
#ifndef _Aft2d_gSegmentPoleEdge_Header
#define _Aft2d_gSegmentPoleEdge_Header

#include <Aft2d_PoleEdgeTemplate.hxx>
#include <Aft2d_gSegmentPoleEdgeFwd.hxx>
#include <Aft2d_gSegmentEdge.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_gSegmentPoleEdge::SingularityContraction
	(
		const Geo2d_MetricPrcsrAnIso&
	);

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gSegmentPoleEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_gPlnCurveSurface>&
		);
}

#endif // !_Aft2d_gSegmentPoleEdge_Header

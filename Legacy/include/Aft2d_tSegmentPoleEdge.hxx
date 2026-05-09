#pragma once
#ifndef _Aft2d_tSegmentPoleEdge_Header
#define _Aft2d_tSegmentPoleEdge_Header

#include <Aft2d_PoleEdgeTemplate.hxx>
#include <Aft2d_tSegmentPoleEdgeFwd.hxx>
#include <Aft2d_tSegmentEdge.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Boolean Aft2d_tSegmentPoleEdge::SingularityContraction
	(
		const Geo2d_MetricPrcsrAnIso&
	);

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Aft2d_tSegmentPoleEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_tPlnCurveSurface>&
		);
}

#endif // !_Aft2d_tSegmentPoleEdge_Header

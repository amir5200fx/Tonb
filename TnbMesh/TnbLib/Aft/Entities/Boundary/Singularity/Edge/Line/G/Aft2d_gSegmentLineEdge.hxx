#pragma once
#ifndef _Aft2d_gSegmentLineEdge_Header
#define _Aft2d_gSegmentLineEdge_Header

#include <Aft2d_LineEdgeTemplate.hxx>
#include <Aft2d_gSegmentLineEdgeFwd.hxx>
#include <Aft2d_gSegmentEdge.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Boolean Aft2d_gSegmentLineEdge::SingularityContraction(const Geo2d_MetricPrcsrAnIso&);

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gSegmentLineEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_gPlnCurveSurface>&
		);
}

#endif // !_Aft2d_gSegmentLineEdge_Header

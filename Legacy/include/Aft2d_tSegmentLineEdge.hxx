#pragma once
#ifndef _Aft2d_tSegmentLineEdge_Header
#define _Aft2d_tSegmentLineEdge_Header

#include <Aft2d_LineEdgeTemplate.hxx>
#include <Aft2d_tSegmentLineEdgeFwd.hxx>
#include <Aft2d_tSegmentEdge.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Boolean 
		Aft2d_tSegmentLineEdge::SingularityContraction(const Geo2d_MetricPrcsrAnIso&);

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Aft2d_tSegmentLineEdge::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_tPlnCurveSurface>&
		);
}

#endif // !_Aft2d_tSegmentLineEdge_Header

#pragma once
#ifndef _Aft2d_tSegmentEdgeUniMetricFwd_Header
#define _Aft2d_tSegmentEdgeUniMetricFwd_Header

#include <Mesh_BndEdge_Position.hxx>
#include <Aft2d_tBndEdgeSurfaceUniMetricTraits.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class BndEdgeTraits, Mesh_BndEdge_Position POS>
	class Mesh_TBndEdge;

	typedef Mesh_TBndEdge<Aft2d_tBndEdgeSurfaceUniMetricTraits, Mesh_BndEdge_Position_Segment>
		Aft2d_tSegmentEdgeUniMetric;
}

#endif // !_Aft2d_tSegmentEdgeUniMetricFwd_Header

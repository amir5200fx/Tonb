#pragma once
#ifndef _Aft2d_gSegmentEdgeUniMetricFwd_Header
#define _Aft2d_gSegmentEdgeUniMetricFwd_Header

#include <Mesh_BndEdge_Position.hxx>
#include <Aft2d_gBndEdgeSurfaceUniMetricTraits.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class BndEdgeTraits, Mesh_BndEdge_Position POS>
	class Mesh_TBndEdge;

	typedef Mesh_TBndEdge<Aft2d_gBndEdgeSurfaceUniMetricTraits, Mesh_BndEdge_Position_Segment>
		Aft2d_gSegmentEdgeUniMetric;
}

#endif // !_Aft2d_gSegmentEdgeUniMetricFwd_Header

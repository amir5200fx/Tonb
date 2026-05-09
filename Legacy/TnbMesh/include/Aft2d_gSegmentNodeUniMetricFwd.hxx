#pragma once
#ifndef _Aft2d_gSegmentNodeUniMetricFwd_Header
#define _Aft2d_gSegmentNodeUniMetricFwd_Header

#include <Mesh_BndNode_Position.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class TBndNodeTraits, Mesh_BndNode_Position POS>
	class Mesh_TBndNode;

	struct Aft2d_gBndNodeSurfaceUniMetricTraits;

	typedef Mesh_TBndNode<Aft2d_gBndNodeSurfaceUniMetricTraits, Mesh_BndNode_Position_Segment>
		Aft2d_gSegmentNodeUniMetric;
}

#endif // !_Aft2d_gSegmentNodeUniMetricFwd_Header

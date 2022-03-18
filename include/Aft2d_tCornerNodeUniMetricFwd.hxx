#pragma once
#ifndef _Aft2d_tCornerNodeUniMetricFwd_Header
#define _Aft2d_tCornerNodeUniMetricFwd_Header

#include <Mesh_BndNode_Position.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class BndNodeTraits, Mesh_BndNode_Position POS>
	class Mesh_TBndNode;

	struct Aft2d_tBndNodeSurfaceUniMetricTraits;

	typedef Mesh_TBndNode<Aft2d_tBndNodeSurfaceUniMetricTraits, Mesh_BndNode_Position_Corner>
		Aft2d_tCornerNodeUniMetric;
}

#endif // !_Aft2d_tCornerNodeUniMetricFwd_Header

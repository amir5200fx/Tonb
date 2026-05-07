#pragma once
#ifndef _Aft2d_CornerNodeUniMetricFwd_Header
#define _Aft2d_CornerNodeUniMetricFwd_Header

#include <Mesh_BndNode_Position.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class BndNodeTraits, Mesh_BndNode_Position POS>
	class Mesh_TBndNode;

	struct Aft2d_TBndNodeUniMetricTraits;

	typedef Mesh_TBndNode<Aft2d_TBndNodeUniMetricTraits, Mesh_BndNode_Position_Corner>
		Aft2d_CornerNodeUniMetric;
}

#endif // !_Aft2d_CornerNodeUniMetricFwd_Header

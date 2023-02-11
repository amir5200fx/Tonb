#pragma once
#ifndef _Geo3d_RingGraphEdgeFwd_Header
#define _Geo3d_RingGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeTraits>
	class Geo_RingGraphEdge;

	struct Geo3d_GraphEdgeTraits;

	typedef Geo_RingGraphEdge<Geo3d_GraphEdgeTraits>
		Geo3d_RingGraphEdge;
}

#endif // !_Geo3d_RingGraphEdgeFwd_Header

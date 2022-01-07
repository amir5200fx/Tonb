#pragma once
#ifndef _Geo2d_RingGraphEdgeFwd_Header
#define _Geo2d_RingGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_RingGraphEdge;

	struct Geo2d_GraphEdgeTraits;

	typedef Geo_RingGraphEdge<Geo2d_GraphEdgeTraits>
		Geo2d_RingGraphEdge;
}

#endif // !_Geo2d_RingGraphEdgeFwd_Header

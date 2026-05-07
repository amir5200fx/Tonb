#pragma once
#ifndef _Geo2d_PolygonRingGraphEdgeFwd_Header
#define _Geo2d_PolygonRingGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_RingGraphEdge;

	struct Geo2d_PolygonGraphEdgeTraits;

	typedef Geo_RingGraphEdge<Geo2d_PolygonGraphEdgeTraits>
		Geo2d_PolygonRingGraphEdge;
}

#endif // !_Geo2d_PolygonRingGraphEdgeFwd_Header

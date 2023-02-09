#pragma once
#ifndef _Geo3d_PolygonRingGraphEdgeFwd_Header
#define _Geo3d_PolygonRingGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeTraits>
	class Geo_RingGraphEdge;

	struct Geo3d_PolygonGraphEdgeTraits;

	typedef Geo_RingGraphEdge<Geo3d_PolygonGraphEdgeTraits>
		Geo3d_PolygonRingGraphEdge;

}

#endif // !_Geo3d_PolygonRingGraphEdgeFwd_Header

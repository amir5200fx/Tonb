#pragma once
#ifndef _Geo2d_PolygonSegmentGraphEdgeFwd_Header
#define _Geo2d_PolygonSegmentGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_SegmentGraphEdge;

	struct Geo2d_PolygonGraphEdgeTraits;

	typedef Geo_SegmentGraphEdge<Geo2d_PolygonGraphEdgeTraits>
		Geo2d_PolygonSegmentGraphEdge;
}

#endif // !_Geo2d_PolygonSegmentGraphEdgeFwd_Header

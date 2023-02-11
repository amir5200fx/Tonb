#pragma once
#ifndef _Geo3d_PolygonSegmentGraphEdgeFwd_Header
#define _Geo3d_PolygonSegmentGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeTraits>
	class Geo_SegmentGraphEdge;

	struct Geo3d_PolygonGraphEdgeTraits;

	typedef Geo_SegmentGraphEdge<Geo3d_PolygonGraphEdgeTraits>
		Geo3d_PolygonSegmentGraphEdge;

}

#endif // !_Geo3d_PolygonSegmentGraphEdgeFwd_Header

#pragma once
#ifndef _Geo2d_SegmentGraphEdgeFwd_Header
#define _Geo2d_SegmentGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_SegmentGraphEdge;

	struct Geo2d_GraphEdgeTraits;

	typedef Geo_SegmentGraphEdge<Geo2d_GraphEdgeTraits>
		Geo2d_SegmentGraphEdge;
}

#endif // !_Geo2d_SegmentGraphEdgeFwd_Header

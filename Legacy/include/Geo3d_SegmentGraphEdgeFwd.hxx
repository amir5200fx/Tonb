#pragma once
#ifndef _Geo3d_SegmentGraphEdgeFwd_Header
#define _Geo3d_SegmentGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeTraits>
	class Geo_SegmentGraphEdge;

	struct Geo3d_GraphEdgeTraits;

	typedef Geo_SegmentGraphEdge<Geo3d_GraphEdgeTraits>
		Geo3d_SegmentGraphEdge;
}

#endif // !_Geo3d_SegmentGraphEdgeFwd_Header

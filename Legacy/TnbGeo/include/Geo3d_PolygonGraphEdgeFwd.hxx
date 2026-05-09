#pragma once
#ifndef _Geo3d_PolygonGraphEdgeFwd_Header
#define _Geo3d_PolygonGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]

	template<class EdgeTraits>
	class Geo_GraphEdge;

	struct Geo3d_PolygonGraphEdgeTraits;

	typedef Geo_GraphEdge<Geo3d_PolygonGraphEdgeTraits>
		Geo3d_PolygonGraphEdge;
}

#endif // !_Geo3d_PolygonGraphEdgeFwd_Header

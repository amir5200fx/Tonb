#pragma once
#ifndef _Geo2d_PolygonGraphEdgeFwd_Header
#define _Geo2d_PolygonGraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_GraphEdge;

	struct Geo2d_PolygonGraphEdgeTraits;

	typedef Geo_GraphEdge<Geo2d_PolygonGraphEdgeTraits>
		Geo2d_PolygonGraphEdge;
}

#endif // !_Geo2d_PolygonGraphEdgeFwd_Header

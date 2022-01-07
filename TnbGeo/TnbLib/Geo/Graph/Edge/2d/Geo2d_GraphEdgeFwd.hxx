#pragma once
#ifndef _Geo2d_GraphEdgeFwd_Header
#define _Geo2d_GraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeTraits>
	class Geo_GraphEdge;

	struct Geo2d_GraphEdgeTraits;

	typedef Geo_GraphEdge<Geo2d_GraphEdgeTraits>
		Geo2d_GraphEdge;
}

#endif // !_Geo2d_GraphEdgeFwd_Header

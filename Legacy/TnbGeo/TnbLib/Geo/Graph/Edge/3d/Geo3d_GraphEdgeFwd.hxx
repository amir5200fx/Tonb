#pragma once
#ifndef _Geo3d_GraphEdgeFwd_Header
#define _Geo3d_GraphEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeTraits>
	class Geo_GraphEdge;

	struct Geo3d_GraphEdgeTraits;

	typedef Geo_GraphEdge<Geo3d_GraphEdgeTraits>
		Geo3d_GraphEdge;
}

#endif // !_Geo3d_GraphEdgeFwd_Header

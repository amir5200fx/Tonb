#pragma once
#ifndef _Geo2d_PolygonGraphNodeFwd_Header
#define _Geo2d_PolygonGraphNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class NodeTraits>
	class Geo_GraphNode;

	struct Geo2d_PolygonGraphNodeTraits;

	typedef Geo_GraphNode<Geo2d_PolygonGraphNodeTraits>
		Geo2d_PolygonGraphNode;
}

#endif // !_Geo2d_PolygonGraphNodeFwd_Header

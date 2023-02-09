#pragma once
#ifndef _Geo3d_PolygonGraphNodeFwd_Header
#define _Geo3d_PolygonGraphNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]

	template<class NodeTraits>
	class Geo_GraphNode;

	struct Geo3d_PolygonGraphNodeTraits;

	typedef Geo_GraphNode<Geo3d_PolygonGraphNodeTraits>
		Geo3d_PolygonGraphNode;
}

#endif // !_Geo3d_PolygonGraphNodeFwd_Header

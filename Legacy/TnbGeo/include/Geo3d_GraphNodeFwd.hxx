#pragma once
#ifndef _Geo3d_GraphNodeFwd_Header
#define _Geo3d_GraphNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class NodeTraits>
	class Geo_GraphNode;

	struct Geo3d_GraphNodeTraits;

	typedef Geo_GraphNode<Geo3d_GraphNodeTraits>
		Geo3d_GraphNode;
}

#endif // !_Geo3d_GraphNodeFwd_Header

#pragma once
#ifndef _Geo2d_GraphNodeFwd_Header
#define _Geo2d_GraphNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class NodeTraits>
	class Geo_GraphNode;

	struct Geo2d_GraphNodeTraits;

	typedef Geo_GraphNode<Geo2d_GraphNodeTraits>
		Geo2d_GraphNode;
}

#endif // !_Geo2d_GraphNodeFwd_Header

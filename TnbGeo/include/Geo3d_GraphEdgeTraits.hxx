#pragma once
#ifndef _Geo3d_GraphEdgeTraits_Header
#define _Geo3d_GraphEdgeTraits_Header

#include <Geo3d_GraphNodeFwd.hxx>

namespace tnbLib
{

	struct Geo3d_GraphEdgeTraits
	{
		typedef Geo3d_GraphNode nodeType;
		typedef void edgeAdaptType;
	};
}

#endif // !_Geo3d_GraphEdgeTraits_Header

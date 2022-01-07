#pragma once
#ifndef _Geo2d_GraphEdgeTraits_Header
#define _Geo2d_GraphEdgeTraits_Header

#include <Geo2d_GraphNodeFwd.hxx>

namespace tnbLib
{

	struct Geo2d_GraphEdgeTraits
	{
		typedef Geo2d_GraphNode nodeType;
		typedef void edgeAdaptType;
	};
}

#endif // !_Geo2d_GraphEdgeTraits_Header

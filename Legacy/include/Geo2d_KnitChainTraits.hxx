#pragma once
#ifndef _Geo2d_KnitChainTraits_Header
#define _Geo2d_KnitChainTraits_Header

#include <Geo2d_GraphNodeFwd.hxx>
#include <Geo2d_SegmentGraphEdgeFwd.hxx>
#include <Geo2d_PolygonGraphFwd.hxx>

namespace tnbLib
{

	struct Geo2d_KnitChainTraits
	{
		typedef Geo2d_PolygonGraph graphType;
		typedef Geo2d_GraphNode nodeType;
		typedef Geo2d_SegmentGraphEdge edgeType;
	};
}

#endif // !_Geo2d_KnitChainTraits_Header

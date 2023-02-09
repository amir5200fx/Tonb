#pragma once
#ifndef _Geo3d_KnitChainTraits_Header
#define _Geo3d_KnitChainTraits_Header

#include <Geo3d_GraphNodeFwd.hxx>
#include <Geo3d_SegmentGraphEdgeFwd.hxx>
#include <Geo3d_PolygonGraphFwd.hxx>

namespace tnbLib
{

	struct Geo3d_KnitChainTraits
	{
		typedef Geo3d_PolygonGraph graphType;
		typedef Geo3d_GraphNode nodeType;
		typedef Geo3d_SegmentGraphEdge edgeType;
	};
}

#endif // !_Geo3d_KnitChainTraits_Header

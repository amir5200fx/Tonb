#pragma once
#ifndef _Geo3d_PolygonGraphEdgeTraits_Header
#define _Geo3d_PolygonGraphEdgeTraits_Header

#include <Geo3d_PolygonGraphNodeFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>

namespace tnbLib
{

	struct Geo3d_PolygonGraphEdgeTraits
	{
		typedef Geo3d_PolygonGraphNode nodeType;
		typedef Entity3d_Polygon edgeAdaptType;
	};
}

#endif // !_Geo3d_PolygonGraphEdgeTraits_Header

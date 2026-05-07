#pragma once
#ifndef _Geo2d_PolygonGraphEdgeTraits_Header
#define _Geo2d_PolygonGraphEdgeTraits_Header

#include <Geo2d_PolygonGraphNodeFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>

namespace tnbLib
{

	struct Geo2d_PolygonGraphEdgeTraits
	{
		typedef Geo2d_PolygonGraphNode nodeType;
		typedef Entity2d_Polygon edgeAdaptType;
	};
}

#endif // !_Geo2d_PolygonGraphEdgeTraits_Header

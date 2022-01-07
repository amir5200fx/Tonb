#pragma once
#ifndef _Geo2d_PolygonGraphFwd_Header
#define _Geo2d_PolygonGraphFwd_Header

#include <Geo2d_PolygonGraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeType>
	class Geo_Graph;

	typedef Geo_Graph<Geo2d_PolygonGraphEdge> Geo2d_PolygonGraph;
}

#endif // !_Geo2d_PolygonGraphFwd_Header

#pragma once
#ifndef _Geo3d_PolygonGraphFwd_Header
#define _Geo3d_PolygonGraphFwd_Header

#include <Geo3d_PolygonGraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeType>
	class Geo_Graph;

	typedef Geo_Graph<Geo3d_PolygonGraphEdge> Geo3d_PolygonGraph;

}

#endif // !_Geo3d_PolygonGraphFwd_Header

#pragma once
#ifndef _Geo2d_GraphFwd_Header
#define _Geo2d_GraphFwd_Header

#include <Geo2d_GraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class EdgeType>
	class Geo_Graph;

	typedef Geo_Graph<Geo2d_GraphEdge> Geo2d_Graph;
}

#endif // !_Geo2d_GraphFwd_Header

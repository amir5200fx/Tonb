#pragma once
#ifndef _Geo3d_GraphFwd_Header
#define _Geo3d_GraphFwd_Header

#include <Geo3d_GraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class EdgeType>
	class Geo_Graph;

	typedef Geo_Graph<Geo3d_GraphEdge> Geo3d_Graph;
}

#endif // !_Geo3d_GraphFwd_Header

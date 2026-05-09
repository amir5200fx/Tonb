#pragma once
#ifndef _Aft2d_gGraphCurveEdgeFwd_Header
#define _Aft2d_gGraphCurveEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/4/2022 Amir]
	template<class EdgeTraits>
	class Geo_GraphEdge;

	struct Aft2d_gGraphCurveEdge_Traits;

	typedef Geo_GraphEdge<Aft2d_gGraphCurveEdge_Traits>
		Aft2d_gGraphCurveEdge;
}

#endif // !_Aft2d_gGraphCurveEdgeFwd_Header

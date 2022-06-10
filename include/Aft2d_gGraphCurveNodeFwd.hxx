#pragma once
#ifndef _Aft2d_gGraphCurveNodeFwd_Header
#define _Aft2d_gGraphCurveNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations [6/4/2022 Amir]
	template<class NodeTraits>
	class Geo_GraphNode;

	struct Aft2d_gGraphCurveNode_Traits;

	typedef Geo_GraphNode<Aft2d_gGraphCurveNode_Traits>
		Aft2d_gGraphCurveNode;
}

#endif // !_Aft2d_gGraphCurveNodeFwd_Header

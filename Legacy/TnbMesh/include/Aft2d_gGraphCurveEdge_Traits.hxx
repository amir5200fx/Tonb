#pragma once
#ifndef _Aft2d_gGraphCurveEdge_Traits_Header
#define _Aft2d_gGraphCurveEdge_Traits_Header

#include <Aft2d_gGraphCurveNodeFwd.hxx>

namespace tnbLib
{

	struct Aft2d_gGraphCurveEdge_Traits
	{
		typedef Aft2d_gGraphCurveNode nodeType;
		typedef Aft2d_gGraphCurveEdge_Traits edgeAdaptType;
	};
}

#endif // !_Aft2d_gGraphCurveEdge_Traits_Header

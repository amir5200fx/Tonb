#pragma once
#ifndef _Aft2d_gGraphCurveNode_Traits_Header
#define _Aft2d_gGraphCurveNode_Traits_Header

#include <Aft2d_gGraphCurveEdgeFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	struct Aft2d_gGraphCurveNode_Traits
	{
		typedef Aft2d_gGraphCurveEdge edgeType;
		typedef Pnt2d ptType;
		typedef void nodeAdaptType;
	};
}

#endif // !_Aft2d_gGraphCurveNode_Traits_Header


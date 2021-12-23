#pragma once
#ifndef _Aft2d_BndEdgeSurfaceTraits_Header
#define _Aft2d_BndEdgeSurfaceTraits_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_BndNodeSurfaceFwd.hxx>

namespace tnbLib
{

	struct Aft2d_BndEdgeSurfaceTraits
	{
		typedef Aft2d_BndNodeSurface nodeType;
		typedef Aft2d_EdgeSurface edgeType;
		typedef void facetType;
	};
}

#endif // !_Aft2d_BndEdgeSurfaceTraits_Header

#pragma once
#ifndef _Aft2d_BndEdgeTraits_Header
#define _Aft2d_BndEdgeTraits_Header

#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_BndNodeFwd.hxx>

namespace tnbLib
{

	struct Aft2d_BndEdgeTraits
	{
		typedef Aft2d_BndNode nodeType;
		typedef Aft2d_Edge edgeType;
		typedef void bndEdgeType;
		typedef void facetType;
	};
}

#endif // !_Aft2d_BndEdgeTraits_Header

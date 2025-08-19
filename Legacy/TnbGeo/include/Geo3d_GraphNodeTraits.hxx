#pragma once
#ifndef _Geo3d_GraphNodeTraits_Header
#define _Geo3d_GraphNodeTraits_Header

#include <Geo3d_GraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	class Pnt3d;

	struct Geo3d_GraphNodeTraits
	{
		typedef Geo3d_GraphEdge edgeType;
		typedef Pnt3d ptType;
		typedef void nodeAdaptType;
	};
}

#endif // !_Geo3d_GraphNodeTraits_Header

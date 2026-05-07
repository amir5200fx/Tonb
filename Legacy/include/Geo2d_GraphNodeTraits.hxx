#pragma once
#ifndef _Geo2d_GraphNodeTraits_Header
#define _Geo2d_GraphNodeTraits_Header

#include <Geo2d_GraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	class Pnt2d;

	struct Geo2d_GraphNodeTraits
	{
		typedef Geo2d_GraphEdge edgeType;
		typedef Pnt2d ptType;
		typedef void nodeAdaptType;
	};
}

#endif // !_Geo2d_GraphNodeTraits_Header

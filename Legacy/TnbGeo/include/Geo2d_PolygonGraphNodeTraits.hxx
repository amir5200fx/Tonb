#pragma once
#ifndef _Geo2d_PolygonGraphNodeTraits_Header
#define _Geo2d_PolygonGraphNodeTraits_Header

#include <Geo2d_PolygonGraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	class Pnt2d;

	struct Geo2d_PolygonGraphNodeTraits
	{
		typedef Geo2d_PolygonGraphEdge edgeType;
		typedef Pnt2d ptType;
		typedef void nodeAdaptType;
	};
}

#endif // !_Geo2d_PolygonGraphNodeTraits_Header

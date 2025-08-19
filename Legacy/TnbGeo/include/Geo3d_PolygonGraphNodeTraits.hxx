#pragma once
#ifndef _Geo3d_PolygonGraphNodeTraits_Header
#define _Geo3d_PolygonGraphNodeTraits_Header

#include <Geo3d_PolygonGraphEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]

	class Pnt3d;

	struct Geo3d_PolygonGraphNodeTraits
	{
		typedef Geo3d_PolygonGraphEdge edgeType;
		typedef Pnt3d ptType;
		typedef void nodeAdaptType;
	};
}

#endif // !_Geo3d_PolygonGraphNodeTraits_Header

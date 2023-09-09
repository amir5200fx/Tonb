#pragma once
#ifndef _Entity2d_QuadMeshFwd_Header
#define _Entity2d_QuadMeshFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{
	// Forward Declarations
	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	class Pnt2d;

	typedef Entity_StaticData<Pnt2d, connectivity::quadruple, false>
		Entity2d_QuadMesh;
	
}

#endif // !_Entity2d_QuadMeshFwd_Header

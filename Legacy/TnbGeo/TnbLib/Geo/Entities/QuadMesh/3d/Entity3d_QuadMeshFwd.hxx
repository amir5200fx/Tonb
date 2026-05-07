#pragma once
#ifndef _Entity3d_QuadMeshFwd_Header
#define _Entity3d_QuadMeshFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{
	// Forward Declarations
	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	class Pnt3d;

	typedef Entity_StaticData<Pnt3d, connectivity::quadruple_3d, false>
		Entity3d_QuadMesh;
}

#endif
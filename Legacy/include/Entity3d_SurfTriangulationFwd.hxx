#pragma once
#ifndef _Entity3d_SurfTriangulationFwd_Header
#define _Entity3d_SurfTriangulationFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	// Forward Declarations [6/11/2023 Payvand]
	class Entity3d_SPnt;

	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	typedef Entity_StaticData<Entity3d_SPnt, connectivity::triple, false>
		Entity3d_SurfTriangulation;
}

#endif // !_Entity3d_SurfTriangulationFwd_Header

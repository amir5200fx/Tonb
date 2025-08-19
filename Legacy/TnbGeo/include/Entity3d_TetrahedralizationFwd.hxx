#pragma once
#ifndef _Entity3d_TetrahedralizationFwd_Header
#define _Entity3d_TetrahedralizationFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	// Forward Declarations [6/24/2022 Amir]
	class Pnt3d;

	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	typedef Entity_StaticData<Pnt3d, connectivity::quadruple, false>
		Entity3d_Tetrahedralization;
}

#endif // !_Entity3d_TetrahedralizationFwd_Header

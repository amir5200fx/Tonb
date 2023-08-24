#pragma once
#ifndef _Entity3d_PentahedralizationFwd_Header
#define _Entity3d_PentahedralizationFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	// Forward Declarations [8/11/2023 aamir]
	class Pnt3d;

	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	typedef Entity_StaticData<Pnt3d, connectivity::sextuple, false>
		Entity3d_Pentahedrolization;
}

#endif // !_Entity3d_PentahedralizationFwd_Header

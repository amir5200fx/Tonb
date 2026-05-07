#pragma once
#ifndef _Entity3d_HexahedralizationFwd_Header
#define _Entity3d_HexahedralizationFwd_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{
	// Forward Declarations
	class Pnt3d;

	template<class Point, class ConnectType, bool NeighbData>
	class Entity_StaticData;

	typedef Entity_StaticData<Pnt3d, connectivity::octuple, false>
		Entity3d_Hexahedralization;
}

#endif
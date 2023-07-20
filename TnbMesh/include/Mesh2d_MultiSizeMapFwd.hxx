#pragma once
#ifndef _Mesh2d_MultiSizeMapFwd_Header
#define _Mesh2d_MultiSizeMapFwd_Header

#include <GeoMesh2d_BackgroundFwd.hxx>

namespace tnbLib
{

	// Forward declarations [7/17/2023 Payvand]
	template<class BackMeshData>
	class Mesh_MultiSizeMap;

	typedef Mesh_MultiSizeMap<GeoMesh2d_Background>
		Mesh2d_MultiSizeMap;
}

#endif // !_Mesh2d_MultiSizeMapFwd_Header

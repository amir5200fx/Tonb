#pragma once
#ifndef _Mesh3d_MultiSizeMapFwd_Header
#define _Mesh3d_MultiSizeMapFwd_Header

#include <GeoMesh3d_BackgroundFwd.hxx>

namespace tnbLib
{

	// Forward declarations [12/7/2022 Payvand]

	template<class BackMeshData>
	class Mesh_MultiSizeMap;

	typedef Mesh_MultiSizeMap<GeoMesh3d_Background>
		Mesh3d_MultiSizeMap;
}

#endif // !_Mesh3d_MultiSizeMapFwd_Header

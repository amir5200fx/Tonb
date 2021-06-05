#pragma once
#ifndef _Mesh2d_UnionSizeMapFwd_Header
#define _Mesh2d_UnionSizeMapFwd_Header

#include <GeoMesh2d_BackgroundFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations

	template<class BackMeshData> class Mesh_UnionSizeMap;

	typedef Mesh_UnionSizeMap<GeoMesh2d_Background> Mesh2d_UnionSizeMap;
}

#endif // !_Mesh2d_UnionSizeMapFwd_Header

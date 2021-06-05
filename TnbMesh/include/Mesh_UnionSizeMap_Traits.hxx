#pragma once
#ifndef _Mesh_UnionSizeMap_Traits_Header
#define _Mesh_UnionSizeMap_Traits_Header

#include <GeoMesh2d_BackgroundFwd.hxx>
#include <GeoMesh2d_MetricBackgroundFwd.hxx>
#include <GeoMesh3d_BackgroundFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class Pnt2d;
	class Pnt3d;

	template<class BackMeshData> struct Mesh_UnionSizeMap_Traits {};

	template<> struct Mesh_UnionSizeMap_Traits<GeoMesh2d_Background> { typedef Pnt2d Point; };
	template<> struct Mesh_UnionSizeMap_Traits<GeoMesh2d_MetricBackground> { typedef Pnt2d Point; };
	template<> struct Mesh_UnionSizeMap_Traits<GeoMesh3d_Background> { typedef Pnt3d Point; };
}

#endif // !_Mesh_UnionSizeMap_Traits_Header

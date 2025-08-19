#pragma once
#ifndef _Mesh_MultiSizeMapTraits_Header
#define _Mesh_MultiSizeMapTraits_Header

#include <GeoMesh3d_BackgroundFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/7/2022 Payvand]
	class Pnt3d;
	class Pnt2d;

	template<class BackMeshData>
	struct multi_sizeMap_dimension {};

	template<>
	struct multi_sizeMap_dimension<GeoMesh3d_Background> { typedef Pnt3d coord; };

	template<>
	struct multi_sizeMap_dimension<GeoMesh2d_Background> { typedef Pnt2d coord; };
}

#endif // !_Mesh_MultiSizeMapTraits_Header

#pragma once
#ifndef _VoyageGeo_VelocityBackgroundFwd_Header
#define _VoyageGeo_VelocityBackgroundFwd_Header

#include <GeoMesh2d_DataFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_SingleBackground;

	class Vec2d;

	typedef GeoMesh_SingleBackground<GeoMesh2d_Data, Vec2d>
		VoyageGeo_VelocityBackground;
}

#endif // !_VoyageGeo_VelocityBackgroundFwd_Header

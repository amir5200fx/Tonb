#pragma once
#ifndef _VoyageGeo_SingleVelocityBackgroundFwd_Header
#define _VoyageGeo_SingleVelocityBackgroundFwd_Header

#include <GeoMesh2d_DataFwd.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_SingleBackground;

	class Vec2d;

	typedef GeoMesh_SingleBackground<GeoMesh2d_Data, Vec2d>
		VoyageGeo_SingleVelocityBackground;
}

#endif // !_VoyageGeo_SingleVelocityBackgroundFwd_Header

#pragma once
#ifndef _VoyageGeo_SingleVelocityBackgroundFwd_Header
#define _VoyageGeo_SingleVelocityBackgroundFwd_Header

#include <Standard_TypeDef.hxx>
#include <GeoMesh2d_DataFwd.hxx>

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

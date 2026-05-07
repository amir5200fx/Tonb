#pragma once
#ifndef _GeoMesh2d_SingleBackgroundFwd_Header
#define _GeoMesh2d_SingleBackgroundFwd_Header

#include <GeoMesh2d_DataFwd.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_SingleBackground;

	typedef GeoMesh_SingleBackground<GeoMesh2d_Data, Standard_Real>
		GeoMesh2d_SingleBackground;
}

#endif // !_GeoMesh2d_SingleBackgroundFwd_Header

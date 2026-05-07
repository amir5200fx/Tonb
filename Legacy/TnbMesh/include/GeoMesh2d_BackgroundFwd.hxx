#pragma once
#ifndef _GeoMesh2d_BackgroundFwd_Header
#define _GeoMesh2d_BackgroundFwd_Header

#include <GeoMesh2d_DataFwd.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_Background;

	typedef GeoMesh_Background<GeoMesh2d_Data, Standard_Real>
		GeoMesh2d_Background;
}

#endif // !_GeoMesh2d_BackgroundFwd_Header
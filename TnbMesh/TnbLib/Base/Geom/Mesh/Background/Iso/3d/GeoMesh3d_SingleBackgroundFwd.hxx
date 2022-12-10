#pragma once
#ifndef _GeoMesh3d_SingleBackgroundFwd_Header
#define _GeoMesh3d_SingleBackgroundFwd_Header

#include <Standard_TypeDef.hxx>
#include <GeoMesh3d_DataFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_SingleBackground;

	typedef GeoMesh_SingleBackground<GeoMesh3d_Data, Standard_Real>
		GeoMesh3d_SingleBackground;
}

#endif // !_GeoMesh3d_SingleBackgroundFwd_Header

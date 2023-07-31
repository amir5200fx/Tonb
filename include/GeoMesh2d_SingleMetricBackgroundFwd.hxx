#pragma once
#ifndef _GeoMesh2d_SingleMetricBackgroundFwd_Header
#define _GeoMesh2d_SingleMetricBackgroundFwd_Header

#include <Standard_TypeDef.hxx>
#include <GeoMesh2d_DataFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class MeshData, class Type>
	class GeoMesh_SingleBackground;

	class Entity2d_Metric1;

	typedef GeoMesh_SingleBackground<GeoMesh2d_Data, Entity2d_Metric1>
		GeoMesh2d_SingleMetricBackground;
}

#endif // !_GeoMesh2d_SingleMetricBackgroundFwd_Header

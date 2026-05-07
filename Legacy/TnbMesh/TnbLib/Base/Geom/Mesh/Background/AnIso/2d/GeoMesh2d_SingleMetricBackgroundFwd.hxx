#pragma once
#ifndef _GeoMesh2d_SingleMetricBackgroundFwd_Header
#define _GeoMesh2d_SingleMetricBackgroundFwd_Header

#include <GeoMesh2d_DataFwd.hxx>
#include <Global_TypeDef.hxx>

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

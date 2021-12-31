#pragma once
#ifndef _Entity2d_MetricMeshValueFwd_Header
#define _Entity2d_MetricMeshValueFwd_Header

#include <Entity2d_TriangulationFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/30/2021 Amir]
	template<class MeshType, class ValueType>
	class Entity_MeshValue;

	class Entity2d_Metric1;

	typedef Entity_MeshValue<Entity2d_Triangulation, Entity2d_Metric1>
		Entity2d_MetricMeshValue;
}

#endif // !_Entity2d_MetricMeshValueFwd_Header

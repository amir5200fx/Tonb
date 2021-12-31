#pragma once
#ifndef _Entity2d_MeshValueFwd_Header
#define _Entity2d_MeshValueFwd_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_TriangulationFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/30/2021 Amir]
	template<class MeshType, class ValueType>
	class Entity_MeshValue;

	typedef Entity_MeshValue<Entity2d_Triangulation, Standard_Real>
		Entity2d_MeshValue;
}

#endif // !_Entity2d_MeshValueFwd_Header

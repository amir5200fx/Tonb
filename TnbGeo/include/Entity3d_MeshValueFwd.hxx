#pragma once
#ifndef _Entity3d_MeshValueFwd_Header
#define _Entity3d_MeshValueFwd_Header

#include <Standard_TypeDef.hxx>
#include <Entity3d_TriangulationFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/30/2021 Amir]
	template<class MeshType, class ValueType>
	class Entity_MeshValue;

	typedef Entity_MeshValue<Entity3d_Triangulation, Standard_Real>
		Entity3d_MeshValue;
}

#endif // !_Entity3d_MeshValueFwd_Header

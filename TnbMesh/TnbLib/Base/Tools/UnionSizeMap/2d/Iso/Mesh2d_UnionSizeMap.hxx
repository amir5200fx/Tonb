#pragma once
#ifndef _Mesh2d_UnionSizeMap_Header
#define _Mesh2d_UnionSizeMap_Header

#include <Entity2d_BoxFwd.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_UnionSizeMap.hxx>
#include <Mesh2d_UnionSizeMapFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Boolean 
		Mesh2d_UnionSizeMap::TreeObject::Subdivide
		(
			const Entity2d_Box&
		) const;

	template<>
	static TnbMesh_EXPORT Standard_Boolean 
		Mesh2d_UnionSizeMap::TreeObject::Subdivider
		(
			const Entity2d_Box&,
			const TreeObject*
		);

	template<>
	TnbMesh_EXPORT void Mesh2d_UnionSizeMap::Perform();
}

#endif // !_Mesh2d_UnionSizeMap_Header

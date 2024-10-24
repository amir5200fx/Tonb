#pragma once
#ifndef _Geo3d_CompressMesh_CompositeFwd_Header
#define _Geo3d_CompressMesh_CompositeFwd_Header

namespace tnbLib
{
	// Forward Declarations
	template<class Mesh>
	class Geo_CompressMesh;

	class Entity3d_CmpMesh;

	typedef Geo_CompressMesh<Entity3d_CmpMesh>
		Geo3d_CompressMesh_Composite;
}
#endif
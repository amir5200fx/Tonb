#pragma once
#ifndef _Geo2d_CompressMesh_CompositeFwd_Header
#define _Geo2d_CompressMesh_CompositeFwd_Header

namespace tnbLib
{
	// Forward Declarations
	template<class Mesh>
	class Geo_CompressMesh;

	class Entity2d_CmpMesh;

	typedef Geo_CompressMesh<Entity2d_CmpMesh>
		Geo2d_CompressMesh_Composite;
}
#endif
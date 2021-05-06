#pragma once
#ifndef _MeshBase_Tools_Header
#define _MeshBase_Tools_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_Module.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	class MeshBase_Tools
	{

	public:

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources,
			const Standard_Real theBaseSize, 
			GeoMesh2d_Background& theMesh
		);

	};
}

#endif // !_MeshBase_Tools_Header

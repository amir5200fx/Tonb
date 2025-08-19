#pragma once
#ifndef _Mesh3d_gShellFwd_Header
#define _Mesh3d_gShellFwd_Header

#include <Mesh3d_gSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2023 Payvand]

	template<class MeshSurf>
	class Mesh_Shell;

	typedef Mesh_Shell<Mesh3d_gSurface> Mesh3d_gShell;
}

#endif // !_Mesh3d_gShellFwd_Header

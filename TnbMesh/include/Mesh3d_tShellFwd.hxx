#pragma once
#ifndef _Mesh3d_tShellFwd_Header
#define _Mesh3d_tShellFwd_Header

#include <Mesh3d_tSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2023 Payvand]

	template<class MeshSurf>
	class Mesh_Shell;

	typedef Mesh_Shell<Mesh3d_tSurface> Mesh3d_tShell;
}

#endif // !_Mesh3d_tShellFwd_Header

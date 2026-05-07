#pragma once
#ifndef _Mesh3d_tShell_Header
#define _Mesh3d_tShell_Header

#include <Mesh3d_tShellFwd.hxx>
#include <Mesh_Shell.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_tShell::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_tShell::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh3d_tShell_Header

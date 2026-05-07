#ifdef MeshCurveAnIso_Debug
#pragma once
#ifndef _Mesh2d_CurveOptmPointAnIso_BisectCorrection_Initial_Header
#define _Mesh2d_CurveOptmPointAnIso_BisectCorrection_Initial_Header

#include <Mesh2d_CurveOptmPointAnIso_BisectCorrection_InitialFwd.hxx>
#include <Mesh_CurveOptmPoint_BisectCorrection_Initial.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Mesh2d_CurveOptmPointAnIso_BisectCorrection_Initial::Perform();
}

#endif // !_Mesh2d_CurveOptmPointAnIso_BisectCorrection_Initial_Header
#endif // MeshCurveAnIso_Debug

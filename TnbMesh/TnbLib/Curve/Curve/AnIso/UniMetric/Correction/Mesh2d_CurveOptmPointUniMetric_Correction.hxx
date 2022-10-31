#ifdef MeshCurveAnIso_Debug
#pragma once
#ifndef _Mesh2d_CurveOptmPointUniMetric_Correction_Header
#define _Mesh2d_CurveOptmPointUniMetric_Correction_Header

#include <Mesh2d_CurveOptmPointUniMetric_CorrectionFwd.hxx>
#include <Mesh_CurveOptmPoint_Correction.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Mesh2d_CurveOptmPointUniMetric_Correction::Perform();
}

#endif // !_Mesh2d_CurveOptmPointUniMetric_Correction_Header
#endif // MeshCurveAnIso_Debug

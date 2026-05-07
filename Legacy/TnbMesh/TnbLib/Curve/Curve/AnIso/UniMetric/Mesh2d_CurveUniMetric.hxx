#pragma once
#ifndef _Mesh2d_CurveUniMetric_Header
#define _Mesh2d_CurveUniMetric_Header

#include <Mesh2d_CurveUniMetricFwd.hxx>
#include <Mesh_Curve.hxx>
#include <Mesh2d_CurveEntityUniMetric.hxx>

#ifdef MeshCurveAnIso_Debug
namespace tnbLib
{
	template<>
	static TnbMesh_EXPORT Standard_Real
		Mesh2d_CurveUniMetric::CalcNextParameter
		(
			const Standard_Real theU0,
			const Standard_Real theGuess,
			const Standard_Real theStep,
			const Standard_Real theUmax,
			const Standard_Integer theLevel,
			const Standard_Integer theMaxLevel,
			const Mesh2d_CurveEntityUniMetric & theCurve,
			const Mesh_Curve_Info & theInfo
		);

	template<>
	Standard_Real Mesh2d_CurveUniMetric::Perform();
}
#endif // MeshCurveAnIso_Debug

#endif // !_Mesh2d_CurveUniMetric_Header

#pragma once
#ifndef _Mesh2d_CurveAnIso_Header
#define _Mesh2d_CurveAnIso_Header

#include <Mesh2d_CurveAnIsoFwd.hxx>
#include <Mesh_Curve.hxx>
#include <Mesh2d_CurveEntityAnIso.hxx>


#ifdef MeshCurveAnIso_Debug
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_CurveAnIso::Perform();
	template <>
	TnbMesh_EXPORT Standard_Real Mesh2d_CurveAnIso::NextParameter(const Standard_Real u0);

	template<>
	TnbMesh_EXPORT Standard_Real
		Mesh2d_CurveAnIso::CalcNextParameter
		(
			const Standard_Real theU0, 
			const Standard_Real theGuess, 
			const Standard_Real theStep, 
			const Standard_Real theUmax,
			const Standard_Integer theLevel,
			const Standard_Integer theMaxLevel,
			const Mesh2d_CurveEntityAnIso & theCurve,
			const Mesh_Curve_Info & theInfo
		);
}
#endif // MeshCurveAnIso_Debug


#endif // !_Mesh2d_CurveAnIso_Header
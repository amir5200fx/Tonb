#pragma once
#ifndef _Mesh2d_PlnCurve_Header
#define _Mesh2d_PlnCurve_Header

#include <Mesh_PlnCurve.hxx>
#include <Mesh2d_PlnCurveFwd.hxx>

namespace tnbLib
{

	template<>
	Handle(Geom2d_Curve) Mesh2d_PlnCurve::Geometry() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurve::FirstParameter() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurve::LastParameter() const;

	template<>
	TnbMesh_EXPORT Pnt2d Mesh2d_PlnCurve::Value(const Standard_Real) const;

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurve::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurve::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnCurve_Header

#pragma once
#ifndef _Mesh2d_PlnCurveAnIso_Header
#define _Mesh2d_PlnCurveAnIso_Header

#include <Mesh_PlnCurve.hxx>
#include <Mesh2d_PlnCurveAnIsoFwd.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Handle(Geom2d_Curve) Mesh2d_PlnCurveAnIso::Geometry() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurveAnIso::FirstParameter() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurveAnIso::LastParameter() const;

	template<>
	TnbMesh_EXPORT Pnt2d Mesh2d_PlnCurveAnIso::Value(const Standard_Real) const;

	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveAnIso::Reverse();

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnCurveAnIso_Header

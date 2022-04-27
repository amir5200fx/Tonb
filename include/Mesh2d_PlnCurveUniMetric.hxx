#pragma once
#ifndef _Mesh2d_PlnCurveUniMetric_Header
#define _Mesh2d_PlnCurveUniMetric_Header

#include <Mesh_PlnCurve.hxx>
#include <Mesh2d_PlnCurveUniMetricFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Handle(Geom2d_Curve) Mesh2d_PlnCurveUniMetric::Geometry() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurveUniMetric::FirstParameter() const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_PlnCurveUniMetric::LastParameter() const;

	template<>
	TnbMesh_EXPORT Pnt2d Mesh2d_PlnCurveUniMetric::Value(const Standard_Real) const;

	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveUniMetric::Reverse();

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnCurveUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnCurveUniMetric_Header

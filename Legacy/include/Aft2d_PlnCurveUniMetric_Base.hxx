#pragma once
#ifndef _Aft2d_PlnCurveUniMetric_Base_Header
#define _Aft2d_PlnCurveUniMetric_Base_Header

#include <Mesh_PlnCurve.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>

namespace tnbLib
{
	template<>
	static TnbMesh_EXPORT std::shared_ptr<Entity2d_Polygon>
		Mesh_PlnCurve_Base::Mesh<Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_PlnCurveUniMetric_Base_Header

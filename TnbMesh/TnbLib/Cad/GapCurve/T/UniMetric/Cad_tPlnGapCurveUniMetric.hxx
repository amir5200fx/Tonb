#pragma once
#ifndef _Cad_tPlnGapCurveUniMetric_Header
#define _Cad_tPlnGapCurveUniMetric_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad_tPlnGapCurveUniMetricFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>,
		std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>
		>
		Cad_tPlnGapCurveUniMetric::Split(const Standard_Real x) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>
		Cad_tPlnGapCurveUniMetric::TopoMesh<Aft2d_tSegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_tPlnGapCurveUniMetric_Header

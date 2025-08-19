#pragma once
#ifndef _Cad_gPlnGapCurveUniMetric_Header
#define _Cad_gPlnGapCurveUniMetric_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad_gPlnGapCurveUniMetricFwd.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>,
		std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>
		>
		Cad_gPlnGapCurveUniMetric::Split(const Standard_Real x) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>
		Cad_gPlnGapCurveUniMetric::TopoMesh<Aft2d_gSegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_gPlnGapCurveUniMetric_Header

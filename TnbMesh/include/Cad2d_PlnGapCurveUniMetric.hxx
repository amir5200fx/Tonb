#pragma once
#ifndef _Cad2d_PlnGapCurveUniMetric_Header
#define _Cad2d_PlnGapCurveUniMetric_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad2d_PlnGapCurveUniMetricFwd.hxx>
#include <Aft2d_PlnCurveUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_PlnCurveUniMetric>,
		std::shared_ptr<Aft2d_PlnCurveUniMetric>
		>
		Cad2d_PlnGapCurveUniMetric::Split(const Standard_Real x) const;

	template<>
	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>
		Cad2d_PlnGapCurveUniMetric::TopoMesh<Aft2d_SegmentEdgeUniMetric>
		(
			const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad2d_PlnGapCurveUniMetric_Header

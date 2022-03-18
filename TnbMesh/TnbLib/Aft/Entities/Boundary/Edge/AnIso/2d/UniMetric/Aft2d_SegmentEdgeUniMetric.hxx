#pragma once
#ifndef _Aft2d_SegmentEdgeUniMetric_Header
#define _Aft2d_SegmentEdgeUniMetric_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_BndNodeAnIso.hxx>
#include <Aft2d_TBndEdgeUniMetricTraits.hxx>
#include <Aft2d_SegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>
		Aft2d_SegmentEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon& theChain,
			const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve
		);

	template<>
	static TnbMesh_EXPORT void Aft2d_SegmentEdgeUniMetric::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>& theWire,
		const Standard_Real theTol
	);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SegmentEdgeUniMetric);

#endif // !_Aft2d_SegmentEdgeUniMetric_Header

#pragma once
#ifndef _Aft2d_tSegmentEdgeUniMetric_Header
#define _Aft2d_tSegmentEdgeUniMetric_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_BndNodeSurface.hxx>
#include <Aft2d_tSegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>
		Aft2d_tSegmentEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon& theChain, 
			const std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>& theCurve
		);

	template<>
	static TnbMesh_EXPORT void Aft2d_tSegmentEdgeUniMetric::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>& theWire,
		const Standard_Real theTol
	);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_tSegmentEdgeUniMetric);

#endif // !_Aft2d_tSegmentEdgeUniMetric_Header

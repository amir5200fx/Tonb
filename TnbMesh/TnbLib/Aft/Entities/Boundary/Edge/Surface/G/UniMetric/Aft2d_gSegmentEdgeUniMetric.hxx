#pragma once
#ifndef _Aft2d_gSegmentEdgeUniMetric_Header
#define _Aft2d_gSegmentEdgeUniMetric_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_BndNodeSurface.hxx>
#include <Aft2d_gSegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>
		Aft2d_gSegmentEdgeUniMetric::GetTopology
		(
			const Entity2d_Polygon& theChain, 
			const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>& theCurve
		);

	template<>
	static TnbMesh_EXPORT void Aft2d_gSegmentEdgeUniMetric::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>& theWire, 
		const Standard_Real theTol
	);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_gSegmentEdgeUniMetric);

#endif // !_Aft2d_gSegmentEdgeUniMetric_Header

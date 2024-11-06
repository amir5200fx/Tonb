#pragma once
#ifndef _Aft2d_gSegmentEdge_Header
#define _Aft2d_gSegmentEdge_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_BndNodeSurface.hxx>
#include <Aft2d_gSegmentEdgeFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gSegmentEdge::GetTopology
		(
			const Entity2d_Polygon& theChain,
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve
		);

	template<>
	TnbMesh_EXPORT void Aft2d_gSegmentEdge::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>& theWire,
		const Standard_Real theTol
	);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_gSegmentEdge);

#endif // !_Aft2d_gSegmentEdge_Header

#pragma once
#ifndef _Aft2d_SegmentEdge_Header
#define _Aft2d_SegmentEdge_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_Edge.hxx>
#include <Aft2d_BndNode.hxx>
#include <Aft2d_TBndEdgeTraits.hxx>
#include <Aft2d_SegmentEdgeFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdge>>
		Aft2d_SegmentEdge::GetTopology
		(
			const Entity2d_Polygon& theChain,
			const std::shared_ptr<Aft2d_PlnCurve>& theCurve
		);

	template<>
	TnbMesh_EXPORT void Aft2d_SegmentEdge::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theWire,
		const Standard_Real theTol
	);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SegmentEdge);

#endif // !_Aft2d_SegmentEdge_Header

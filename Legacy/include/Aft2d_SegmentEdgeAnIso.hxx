#pragma once
#ifndef _Aft2d_SegmentEdgeAnIso_Header
#define _Aft2d_SegmentEdgeAnIso_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_BndNodeAnIso.hxx>
#include <Aft2d_TBndEdgeAnIsoTraits.hxx>
#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>
		Aft2d_SegmentEdgeAnIso::GetTopology
		(
			const Entity2d_Polygon& theChain,
			const std::shared_ptr<Aft2d_PlnCurveAnIso>& theCurve
		);

	template<>
	static TnbMesh_EXPORT void Aft2d_SegmentEdgeAnIso::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>& theWire,
		const Standard_Real theTol
	);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_SegmentEdgeAnIso);

#endif // !_Aft2d_SegmentEdgeAnIso_Header

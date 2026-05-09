#pragma once
#ifndef _Aft2d_tSegmentEdge_Header
#define _Aft2d_tSegmentEdge_Header

#include <Mesh_TBndEdge.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_BndNodeSurface.hxx>
#include <Aft2d_tSegmentEdgeFwd.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Aft2d_tSegmentEdge::GetTopology
		(
			const Entity2d_Polygon& theChain, 
			const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve
		);

	template<>
	static TnbMesh_EXPORT void Aft2d_tSegmentEdge::MergeDangles
	(
		const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>& theWire,
		const Standard_Real theTol
	);

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_tSegmentEdge);

#endif // !_Aft2d_tSegmentEdge_Header

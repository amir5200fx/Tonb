#pragma once
#ifndef _Aft2d_SegmentGapEdgeAnIso_Header
#define _Aft2d_SegmentGapEdgeAnIso_Header

#include <Aft2d_GapEdgeTemplate.hxx>
#include <Aft2d_SegmentGapEdgeAnIsoFwd.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_SegmentGapEdgeAnIso::Contraction
	(
		const Geo2d_MetricPrcsrAnIso&
	);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>
		Aft2d_SegmentGapEdgeAnIso::GetTopology
		(
			const Entity2d_Polygon&,
			const std::shared_ptr<Aft2d_PlnCurveAnIso>&
		);
}

#endif // !_Aft2d_SegmentGapEdgeAnIso_Header

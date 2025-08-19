#pragma once
#ifndef _Cad2d_PlnGapCurveAnIso_Header
#define _Cad2d_PlnGapCurveAnIso_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad2d_PlnGapCurveAnIsoFwd.hxx>
#include <Aft2d_PlnCurveAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_PlnCurveAnIso>,
		std::shared_ptr<Aft2d_PlnCurveAnIso>
		>
		Cad2d_PlnGapCurveAnIso::Split(const Standard_Real x) const;

	template<>
	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>
		Cad2d_PlnGapCurveAnIso::TopoMesh<Aft2d_SegmentEdgeAnIso>
		(
			const std::shared_ptr<Aft2d_PlnCurveAnIso>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad2d_PlnGapCurveAnIso_Header
